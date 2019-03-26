#pragma once
#include "GameObject.h"
#include <vector>

class GameObjectManager
{
private:
	vector<GameObject*> gameObjects;
	vector<Vector3f> originalPos;

	const int killTime;
	bool isDead;

private:
	void StoreInitialPosition(GameObject* g);
	void RepositionParticle(GameObject* g);

public:
	GameObjectManager(vector<GameObject*> p);
	GameObjectManager(GameObject * g);
	~GameObjectManager();

	vector<GameObject*> GetGameObjectList()	const							{ return gameObjects; }

	void Update(float t);
	void AddParticle(GameObject * g);
};

