#include "QuadTree.h"

#define MAXOBJECTDENSITY 0
#define MAXLEVELS 10

QuadTree::QuadTree(Quadrant * b, const unsigned lvl) : level(lvl), bounds(b)
{
	for (unsigned char i = 0; i < nodes.size(); i++)
	{
		nodes[i] = nullptr;
	}
}

QuadTree::~QuadTree()
{
	delete bounds;
	bounds = nullptr;

	for (auto& node : nodes)
	{
		delete node;
		node = nullptr;
	}
}

/* Clears quad tree */
void QuadTree::Clear()
{
	gameObjectList.clear();

	for (unsigned char i = 0; i < nodes.size(); i++)
	{
		if (nodes[i])
		{
			nodes[i]->Clear();
			nodes[i] = nullptr;
		}
	}
}

/* Splits node into 4 new sub-nodes */
void QuadTree::Subdivide()
{
	const auto subScale = bounds->position * .25f;
	const auto subPosition = bounds->position;

	CreateNE(subPosition, subScale);
	CreateNW(subPosition, subScale);
	CreateSW(subPosition, subScale);
	CreateSE(subPosition, subScale);
}

void QuadTree::CreateNE(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[NORTHEAST])
		nodes[NORTHEAST] = new QuadTree(new Quadrant(Vector3f(subPosition.x + subScale.x, subPosition.y, subPosition.z + subScale.z), subPosition), level + 1);
}

void QuadTree::CreateNW(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[NORTHWEST])
		nodes[NORTHWEST] = new QuadTree(new Quadrant(Vector3f(subPosition.x - subScale.x, subPosition.y, subPosition.z + subScale.z), level + 1));
}

void QuadTree::CreateSE(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[SOUTHEAST])
		nodes[SOUTHEAST] = new QuadTree(new Quadrant(Vector3f(subPosition.x + subScale.x, subPosition.y, subPosition.z - subScale.z), level + 1));
}

void QuadTree::CreateSW(const Vector3f &subPosition, const Vector3f &subScale)
{
	if (!nodes[SOUTHWEST])
		nodes[SOUTHWEST] = new QuadTree(new Quadrant(Vector3f(subPosition.x - subScale.x, subPosition.y, subPosition.z - subScale.z), level + 1));
}

/*
*Determines which node owns which object.
*-1 means object aren't completely fit within a child node
* of the parent node
*/
int QuadTree::GetIndex(class GameObject* g) const
{
	signed int index = -1;
	const Vector3f midpoint = bounds->position;

	const auto particle = g->GetParticle();
	const auto transform = g->GetTransformation();

	const float radius = particle->GetRadius();	
	const Vector3f position = transform->GetPosition();

	// Can object fully fit inside top quadrant
	const bool topQuad = position.z - radius > midpoint.z;

	// Can object fully fit inside bottom quadrant
	const bool bottomQuad = position.z - radius < midpoint.z && position.z + radius < midpoint.z;

	// Can object completely fit inside left quadrant
	if (position.x - radius < midpoint.x && position.x + radius < midpoint.x) // West-side
	{
		if (topQuad)
			index = NORTHWEST;
		else if (bottomQuad)
			index = SOUTHWEST;
	}
	else if (position.x - radius > midpoint.x) // East-side
	{
		if (topQuad)
			index = NORTHEAST;
		else if (bottomQuad)
			index = SOUTHEAST;
	}

	return index;
}

void QuadTree::Insert(GameObject *g)
{
	int index = GetIndex(g);

	if (index != -1)
	{
		if (nodes[index] && level < MAXLEVELS)
		{
			nodes[index]->Insert(g);
			return;
		}
	}

	gameObjectList.emplace_back(g);

	if (index != -1)
		if (gameObjectList.size() > MAXOBJECTDENSITY && level < MAXLEVELS)
		{
			if (!nodes[index])
				Subdivide();

			size_t i = 0;

			while (i < gameObjectList.size())
			{
				index = GetIndex(gameObjectList[i]);

				if (index != -1)
				{
					nodes[index]->Insert(gameObjectList[i]);
					gameObjectList.erase(gameObjectList.begin() + i);
				}
				else
					i++;
			}
		}
}

void QuadTree::retrieve(vector<GameObject*>& returnList, GameObject* g)
{
	const int index = GetIndex(g);

	if (index != -1 && nodes[index])
		nodes[index]->retrieve(returnList, g);

	for (auto currentGO : gameObjectList)
	{
		if (g != currentGO)
			returnList.emplace_back(g);
	}
}