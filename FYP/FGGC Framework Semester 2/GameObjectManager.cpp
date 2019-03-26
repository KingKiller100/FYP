#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(vector<GameObject*> g) : killTime(10)
{
	gameObjects = g;
	isDead = false;

	for (GameObject* g : g)
	{
		StoreInitialPosition(g);
	}
}

GameObjectManager::GameObjectManager(GameObject* g) : killTime(10)
{
	gameObjects.push_back(g);
	isDead = false;

	StoreInitialPosition(g);
}

GameObjectManager::~GameObjectManager()
{
	for (GameObject* g : gameObjects)
	{
		if (g)
		{
			delete g;
			g = nullptr;
		}
	}
}

void GameObjectManager::StoreInitialPosition(GameObject* g)
{
	originalPos.push_back(g->GetTransformation()->GetPosition());
}

void GameObjectManager::AddParticle(GameObject* g)
{
	gameObjects.push_back(g);
	StoreInitialPosition(g);
}

void GameObjectManager::RepositionParticle(GameObject* g)
{
	for (int i = gameObjects.size() - 1; i > 1; i--)
	{
		if (g->GetType() == gameObjects[i]->GetType())
		{
			g->GetTransformation()->SetPosition(originalPos[i]);
			g->GetParticle()->SetVelocity(Vector3f());
			g->GetParticle()->SetAcceleration(Vector3f());
		}
	}
}

void GameObjectManager::Update(float t)
{
	for (GameObject* g : gameObjects)
	{
		g->Update(t);

		if (g->GetParticle()->GetLifeTimer() >= killTime && g->GetParticle()->GetIsKillable())
		{
			RepositionParticle(g);
			g->GetParticle()->ResetLifeTimer();
		}
	}
}
