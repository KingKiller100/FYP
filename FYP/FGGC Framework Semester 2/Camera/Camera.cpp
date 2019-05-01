#include "Camera.h"

#define FORWARDMOVEMENT XMVector3Normalize(XMVector3TransformCoord(forwardVector, rotationMatrix))
#define HORIZONTALMOVEMENT XMVector3TransformCoord(horizontalVector, rotationMatrix)

#define MAXVERTICALROTATION 1.35f

Camera::Camera(const UINT &windowHeight, const UINT &windowWidth) : windowHeight(windowHeight), windowWidth(windowWidth), rotationX(0.05f),
																		rotationY(0.05f)
{
	position = XMVectorSet(0, 5, 0, 0);
	at = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	zMoveSpeed = yMoveSpeed = 0.f;

	rotationX = 0.05f;
	rotationY = 0.05f;

	nearDepth = 0.01f;
	farDepth = 100.f;

	turnSpeed = 10.f;

	camAcceleration = 0.000001f;
}

Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
	: position(XMVectorSet(position.x, position.y, position.z, 0)), at(XMVectorSet(at.x, at.y, at.z, 0)), up(XMVectorSet(up.x, up.y, up.z, 0)),
		windowHeight(windowHeight), windowWidth(windowWidth), nearDepth(nearDepth), farDepth(farDepth), rotationX(0.05f),
		rotationY(0.05f)
{
	zMoveSpeed =  yMoveSpeed = 0;

	camAcceleration = 0.000001f;
}

void Camera::Movement()
{
	ForwardMovement();
	BackwardMovement();
	LeftTurn();
	RightTurn();
	Ascension();
	Descension();
	UpwardTurn();
	DownwardTurn();
}

void Camera::ForwardMovement()
{
	if (!GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_UP))
	{
		zMoveSpeed += zMoveSpeed < 0.5f ? camAcceleration : 0;
	}
	else
		zMoveSpeed = 0;
}

void Camera::BackwardMovement()
{
	if (!GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_DOWN))
		zMoveSpeed -= zMoveSpeed < 0.5f ? camAcceleration : 0;
	else
		zMoveSpeed = 0;
}

void Camera::Ascension()
{
	if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_UP))
		yMoveSpeed += yMoveSpeed < 0.5f ? camAcceleration : 0;
	else
		yMoveSpeed = 0;
}

void Camera::Descension()
{
	if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_DOWN))
		yMoveSpeed -= yMoveSpeed < 0.5f ? camAcceleration : 0;
	else
		yMoveSpeed = 0.0f;
}

void Camera::LeftTurn()
{
	rotationY -= GetAsyncKeyState('A') & 0x8000 ? 0.0005f : .0f;
}

void Camera::RightTurn()
{
	rotationY += GetAsyncKeyState('D') & 0x8000 ? 0.0005f : .0f;
}

void Camera::UpwardTurn()
{
	if (GetAsyncKeyState('W') & 0x8000)
		rotationX -= rotationX > -MAXVERTICALROTATION ? 0.0005f : .0f;
}

void Camera::DownwardTurn()
{
	if (GetAsyncKeyState('S') & 0x8000)
		rotationX += rotationX < MAXVERTICALROTATION ? .0005f : 0;
}

void Camera::Update()
{
	Movement();

	RecalculateCamera();

	// Initialize the view matrix
	XMStoreFloat4x4(&view, XMMatrixLookAtLH(position, at, up));

	// Initialize the projection matrix
	XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, windowWidth / windowHeight, nearDepth, farDepth));
}

void Camera::RecalculateCamera()
{	
	static auto forwardVector = XMVectorSet(0, 0, 1, 0);
	static auto horizontalVector = XMVectorSet(1, 0, 0, 0);
	static auto verticalVector = XMVectorSet(0, 1, 0, 0);

	const auto rotationMatrix = XMMatrixRotationRollPitchYaw(rotationX, rotationY, 0);
	
	position += turnSpeed * HORIZONTALMOVEMENT;
	position += zMoveSpeed * FORWARDMOVEMENT;
	position += yMoveSpeed * verticalVector;

	turnSpeed = 0;

	at = position + FORWARDMOVEMENT;
}
