#pragma once
#include "../Patterns/Command.h"
#include "../GameObject/GameObjectManager.h"

class ControllerManager final
{
private:

	static ControllerManager* mInstance;

	char moveForward;
	char moveBackward;
	char moveRight;
	char moveLeft;
	char fly;
	char jump;

	GameObjectManager* _gm;
	int currentObject;

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

	// Movement Accessor Methods
	void SetForwardButton(const char &f)				{ moveForward = f; }
	void SetBackwardButton(const char &b)				{ moveBackward = b; }
	void SetRightButton(const char &r)					{ moveRight = r; }
	void SetLeftButton(const char &l)					{ moveLeft = l; }
	void SetFlyButton(const char &f)					{ fly = f; }
	void SetJumpButton(const char &j)					{ jump = j; }


	// CO Accessor Methods
	void SetCurrentObject(const int co)					{ currentObject = co; }
};

