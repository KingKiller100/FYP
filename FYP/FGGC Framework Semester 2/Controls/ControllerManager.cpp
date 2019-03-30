 #include "ControllerManager.h"
#include "../Physics/Collisions/CollisionsManager.h"

 // Initialise instance to Null
ControllerManager* ControllerManager::mInstance = nullptr;

ControllerManager::ControllerManager()
{
	moveForward = 'W';
	moveLeft = 'A';
	moveBackward = 'S';
	moveRight = 'D';
	fly = 'F';
	jump = 'J';

	currentObject = 1;
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
	// Move particle
	if (GetAsyncKeyState(moveForward)) // forward
	{
		if (GetAsyncKeyState(VK_SHIFT))
			_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 3)));
		else
			_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2)));
	}
	else if (GetAsyncKeyState(moveBackward)) // down
	{
		_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, 0.0f, -powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2)));
	}

	if (GetAsyncKeyState(moveRight)) // right
	{
		_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(-powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	else if (GetAsyncKeyState(moveLeft)) // left
	{
		_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 2), 0.0f, 0.0f));
	}
	if (GetAsyncKeyState(fly)) // fly
	{
		_buttonJ->Execute(*_gm->GetGameObjectList()[currentObject]->GetParticle());
	}
	else if (GetAsyncKeyState(VK_SPACE)) // jump
	{
		if (CollisionsManager::Instance()->CheckBoundingPlane(_gm->GetGameObjectList()[0], _gm->GetGameObjectList()[currentObject]))
			_gm->GetGameObjectList()[currentObject]->GetParticle()->AddForce(Vector3f(0.0f, powf(_gm->GetGameObjectList()[currentObject]->GetParticle()->GetMass(), 3), 0.0f));
	}
}
