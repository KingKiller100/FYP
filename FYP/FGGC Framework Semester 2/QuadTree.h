#pragma once
#include <vector>
#include <array>
#include "GameObject.h"

enum Compass
{
	NORTHEAST = 0,
	NORTHWEST,
	SOUTHWEST,
	SOUTHEAST,
};

struct Quadrant
{
	Vector3f position;
	Vector3f scale;

	Quadrant()
	{
		position = scale = Vector3f();
	}

	Quadrant(const float xVal, const float zVal, const float w = 100, const float h = 100) : position(Vector3f(xVal, 0, zVal)), scale(Vector3f(w, 0, h)) {/* Empty */ }

	Quadrant(const Vector3f &p, const Vector3f &s) : position(p), scale(s)
	{
	}
};

class QuadTree
{
public:
	QuadTree(Quadrant *b, const unsigned lvl = 0);
	~QuadTree();

	void Clear();
	void Insert(GameObject *g);

	void retrieve(vector<GameObject*> &returnList, GameObject* g);

private:
	u_int level;
	std::vector<GameObject*> gameObjectList;
	Quadrant *bounds;
	std::array<QuadTree*, 4> nodes;

private:
	void Subdivide();
	int GetIndex(GameObject *g) const;

	void CreateNE(const Vector3f &subPosition, const Vector3f &subScale);
	void CreateNW(const Vector3f &subPosition, const Vector3f &subScale);
	void CreateSE(const Vector3f &subPosition, const Vector3f &subScale);
	void CreateSW(const Vector3f &subPosition, const Vector3f &subScale);
};
