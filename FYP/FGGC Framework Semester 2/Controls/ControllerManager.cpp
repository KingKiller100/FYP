 #include "ControllerManager.h"

 // Initialise instance to Null
ControllerManager* ControllerManager::mInstance = nullptr;

ControllerManager::ControllerManager()
{
}

void ControllerManager::BindJumpCommand()
{
	_buttonJ = new JumpCommand();
}


ControllerManager::~ControllerManager()
{
	delete mInstance;

	delete _buttonJ;
}

ControllerManager * ControllerManager::Instance()
{
	if (!mInstance)
		mInstance = new ControllerManager;

	return mInstance;
}

void ControllerManager::init(GameObjectManager* p)
{
	_gm = p;
}

void ControllerManager::Update()
{
}
