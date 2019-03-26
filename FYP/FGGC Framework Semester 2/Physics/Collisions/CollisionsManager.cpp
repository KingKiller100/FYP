#include "CollisionsManager.h"

// Initialise the instance to null
CollisionsManager* CollisionsManager::mInstance = nullptr;

CollisionsManager::CollisionsManager()
= default;

CollisionsManager::~CollisionsManager()
{
	mInstance = nullptr;
}

CollisionsManager * CollisionsManager::Instance()
{
	if (!mInstance)
		mInstance = new CollisionsManager;

	return mInstance;
}

bool CollisionsManager::CheckBoundingSphere(GameObject * go1, GameObject * go2) const
{
	const float distance = go1->GetTransformation()->GetPosition().Distance(go2->GetTransformation()->GetPosition());

	return distance < go1->GetParticle()->GetRadius() + go2->GetParticle()->GetRadius();
}

bool CollisionsManager::CheckBoundingBox(GameObject * go1, GameObject * go2)
{
	// Vector3f aVertices[8] =
	// {
	// 	Vector3f(1, 1, 1), // back top right
	// 	Vector3f(1, 1, -1), // front top right
	// 	Vector3f(-1, 1, -1), // front top left
	// 	Vector3f(-1, 1, 1), // back top left
	// 	Vector3f(-1, -1, 1), // back bottom left
	// 	Vector3f(-1, -1,-1), // front bottom right
	// 	Vector3f(1, -1, -1), // front bottom right 
	// 	Vector3f(1, -1, 1), // back bottom right
	// };
	//
	// for (Vector3f v : aVertices)
	// {
	// 	v *= go1->GetParticle()->GetRadius();
	// 	v += go1->GetTransformation()->GetPosition();
	// }
	//
	// Vector3f bVertices[8] =
	// {
	// 	Vector3f(1, 1, 1), // back top right
	// 	Vector3f(1, 1, -1), // front top right
	// 	Vector3f(-1, 1, -1), // front top left
	// 	Vector3f(-1, 1, 1), // back top left
	// 	Vector3f(-1, -1, 1), // back bottom left
	// 	Vector3f(-1, -1,-1), // front bottom right
	// 	Vector3f(1, -1, -1), // front bottom right 
	// 	Vector3f(1, -1, 1), // back bottom right
	// };
	//
	// for (Vector3f v : bVertices)
	// {
	// 	v *= go2->GetParticle()->GetRadius();
	// 	v += go2->GetTransformation()->GetPosition();
	// }
	//
	// return false;
	// //float aMaxX = go1->GetTransformation()->GetPosition().x + go1->GetParticle()->GetRadius();
	// //float aMinX = go1->GetTransformation()->GetPosition().x - go1->GetParticle()->GetRadius();
	// //float aMaxY = go1->GetTransformation()->GetPosition().y + go1->GetParticle()->GetRadius();
	// //float aMinY = go1->GetTransformation()->GetPosition().y - go1->GetParticle()->GetRadius();
	// //float aMaxZ = go1->GetTransformation()->GetPosition().z + go1->GetParticle()->GetRadius();
	// //float aMinZ = go1->GetTransformation()->GetPosition().z - go1->GetParticle()->GetRadius();
	//
	// //float bMaxX = go2->GetTransformation()->GetPosition().x + go2->GetParticle()->GetRadius();
	// //float bMinX = go2->GetTransformation()->GetPosition().x - go2->GetParticle()->GetRadius();
	// //float bMaxY = go2->GetTransformation()->GetPosition().y + go2->GetParticle()->GetRadius();
	// //float bMinY = go2->GetTransformation()->GetPosition().y - go2->GetParticle()->GetRadius();
	// //float bMaxZ = go2->GetTransformation()->GetPosition().z + go2->GetParticle()->GetRadius();
	// //float bMinZ = go2->GetTransformation()->GetPosition().z - go2->GetParticle()->GetRadius();
	//
	// /*return (aMinX <= bMaxX && aMaxX >= bMinX) &&
	// 	(aMinY <= bMaxY && aMaxY >= bMinY) && 
	// 	(aMinZ <= bMaxZ && aMaxZ >= bMinZ);*/

	return false;
}

bool CollisionsManager::CheckBoundingPlane(GameObject * go, GameObject * plane) const
{
	// Store plane data as if it's a 2D shape - only using x and y axis
	const float planeMaxX = plane->GetTransformation()->GetPosition().x + plane->GetTransformation()->GetScale().x;
	const float planeMinX = plane->GetTransformation()->GetPosition().x - plane->GetTransformation()->GetScale().x;
	const float planeMaxY = plane->GetTransformation()->GetPosition().y;
	const float planeMaxZ = plane->GetTransformation()->GetPosition().z + plane->GetTransformation()->GetScale().z;
	const float planeMinZ = plane->GetTransformation()->GetPosition().z - plane->GetTransformation()->GetScale().z;


	const float objectMaxX = go->GetTransformation()->GetPosition().x + go->GetParticle()->GetRadius();
	const float objectMinX = go->GetTransformation()->GetPosition().x - go->GetParticle()->GetRadius();
	const float objectMinY = go->GetTransformation()->GetPosition().y - go->GetParticle()->GetRadius();
	const float objectMaxZ = go->GetTransformation()->GetPosition().z + go->GetParticle()->GetRadius();
	const float objectMinZ = go->GetTransformation()->GetPosition().z - go->GetParticle()->GetRadius();

	return (planeMinX <= objectMaxX && planeMaxX >= objectMinX) && 
		(objectMinY <= planeMaxY) && 
		(planeMinZ <= objectMaxZ && planeMaxZ >= objectMinZ);
}

void CollisionsManager::Separation(GameObject * go1, GameObject* go2)
{
	// Separate objects after inter-object collision
	
	const float radiiSum = go1->GetParticle()->GetRadius() + go2->GetParticle()->GetRadius();
	const float distance = Vector3f::Magnitude(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());
	const float depth = radiiSum - distance;
	const Vector3f direction = Vector3f::Normalize(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());

	const Vector3f object1Pos = go1->GetTransformation()->GetPosition() + direction * depth;
	const Vector3f object2Pos = go2->GetTransformation()->GetPosition() - direction * depth;

	go1->GetTransformation()->SetPosition(object1Pos);
	go2->GetTransformation()->SetPosition(object2Pos);

	ResolveCollision(go1, go2);
}

void CollisionsManager::ResolveCollision(GameObject* go1, GameObject* go2)
{	
	// Resolves after seperating the two objects during collision
	const float e = (go1->GetParticle()->GetCoefficientOfRestitution() + go2->GetParticle()->GetCoefficientOfRestitution()) / 2;

	Vector3f firstRest = go1->GetParticle()->GetVelocity() * (go1->GetParticle()->GetMass() - (go2->GetParticle()->GetMass() * e));
	
	Vector3f secondRest = go2->GetParticle()->GetVelocity() * (go2->GetParticle()->GetMass() * (1.0f + e));

	Vector3f finalVel1 = (firstRest + secondRest) / (go1->GetParticle()->GetMass() + go2->GetParticle()->GetMass());

	firstRest = go1->GetParticle()->GetVelocity() * go1->GetParticle()->GetMass();
	secondRest = go2->GetParticle()->GetVelocity() * go2->GetParticle()->GetMass();

	const Vector3f temp = finalVel1 * go1->GetParticle()->GetMass();
	Vector3f finalVel2 = (firstRest + secondRest - temp) / go2->GetParticle()->GetMass();

	Vector3f norm1 = Vector3f::Normalize(go1->GetTransformation()->GetPosition() - go2->GetTransformation()->GetPosition());
	const Vector3f norm2 = norm1.ReverseVector();

	const Vector3f relativeVel1 = norm1  * Vector3f::DotProduct(norm1, finalVel1);
	const Vector3f relativeVel2 = norm2 * Vector3f::DotProduct(norm2, finalVel2);

	finalVel1 += relativeVel2 - relativeVel1;
	finalVel2 += relativeVel1 - relativeVel2;

	go1->GetParticle()->SetVelocity(finalVel2);
	go2->GetParticle()->SetVelocity(finalVel1);
}

void CollisionsManager::Update(GameObject * go1, GameObject * go2)
{
	if (go1->GetType() == go2->GetType())
		return;
		
	if (CheckBoundingSphere(go1, go2))
			Separation(go1, go2);

	if (go2->GetType() == "Floor")
		if (CheckBoundingPlane(go1, go2))
		{
			go1->GetParticle()->SetVelocity(Vector3f(go1->GetParticle()->GetVelocity().x, go1->GetParticle()->GetVelocity().y * -0.85f, go1->GetParticle()->GetVelocity().z));
			if (go1->GetParticle()->GetVelocity().y < 0.002f)
				go1->GetTransformation()->SetPosition(Vector3f(go1->GetTransformation()->GetPosition().x, go2->GetTransformation()->GetPosition().y + go1->GetParticle()->GetRadius(), go1->GetTransformation()->GetPosition().z));
		}
}