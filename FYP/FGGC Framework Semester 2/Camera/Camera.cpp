#include "Camera.h"
#define FORWARDMOVEMENT XMVector3TransformCoord(forwardVector, rotationMatrix)

Camera::Camera(const UINT &windowHeight, const UINT &windowWidth) : windowHeight(windowHeight), windowWidth(windowWidth)
{
	position = XMVectorSet(0, 5, 0, 1);
	at = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	rotationX = 0.05f;
	rotationY = 0.05f;

	nearDepth = 0.01f;
	farDepth = 100.f;

	turnSpeed = 10.f;
}

Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
	: position(XMVectorSet(position.x, position.y, position.z, 1)), at(XMVectorSet(at.x, at.y, at.z, 1)), up(XMVectorSet(up.x, up.y, up.z, 0)), windowHeight(windowHeight), windowWidth(windowWidth), nearDepth(nearDepth), farDepth(farDepth)
{
	Update();
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
		forwardMoveSpeed += forwardMoveSpeed < 0.5f ? 0.01f : 0;
	else
		forwardMoveSpeed = forwardMoveSpeed > 0.0f ? forwardMoveSpeed - 0.01f : 0.0f;
}

void Camera::BackwardMovement()
{
	if (!GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_DOWN))
		backwardMoveSpeed += backwardMoveSpeed < 0.5f ? 0.01f : 0;
	else
		backwardMoveSpeed = backwardMoveSpeed > 0.0f ? backwardMoveSpeed - 0.01f : 0.0f;
}

void Camera::Ascension()
{
	if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_UP))
		ascendingSpeed += ascendingSpeed < 0.5f ? 0.01f : 0;
	else
		ascendingSpeed = ascendingSpeed > 0.0f ? ascendingSpeed - 0.02f : 0.0f;
}

void Camera::Descension()
{
	if (GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState(VK_DOWN))
		descendingSpeed += descendingSpeed < 0.5f ? 0.01f : 0;
	else
		descendingSpeed = descendingSpeed > 0.0f ? descendingSpeed - 0.02f : 0.0f;
}

void Camera::LeftTurn()
{
	rotationY -= GetAsyncKeyState('A') & 0x8000 ? 0.05f : .0f;
}

void Camera::RightTurn()
{
	rotationY += GetAsyncKeyState('D') & 0x8000 ? 0.05f : .0f;
}

void Camera::UpwardTurn()
{
	if (GetAsyncKeyState('W') & 0x8000)
		rotationX -= rotationX > -1.35 ? 0.05f : .0f;
}

void Camera::DownwardTurn()
{
	if (GetAsyncKeyState('S') & 0x8000)
		rotationX += rotationX < 1.35 ? .05f : 0;
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
	auto target = XMVector3TransformCoord(forwardVector, rotationMatrix);
	target = XMVector3Normalize(target);

	const auto camHorizontal = XMVector3TransformCoord(horizontalVector, rotationMatrix);
	// const auto camForward = ;

	position += turnSpeed * camHorizontal;

	position += forwardMoveSpeed * FORWARDMOVEMENT;
	position -= backwardMoveSpeed * FORWARDMOVEMENT;

	position += ascendingSpeed * verticalVector;
	position -= descendingSpeed * verticalVector;

	turnSpeed = 0;

	at = position + target;
}