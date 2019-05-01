#pragma once
#include "../Patterns/Command.h"
#include "../GameObject/GameObjectManager.h"

class ControllerManager final
{
private:
	static ControllerManager* mInstance;
	
	GameObjectManager* _gm;

	Command* _buttonJ;

private:
	ControllerManager();

	void BindJumpCommand();

public:
	~ControllerManager();
	ControllerManager(const ControllerManager &) = delete;
	ControllerManager(const ControllerManager &&) = delete;

	static ControllerManager* Instance();
	void init(GameObjectManager* p);

	void Update();
};

