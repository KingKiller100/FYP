#pragma once

#include <windows.h>
#include <directxmath.h>

using namespace DirectX;

class Camera
{
private:
	XMVECTOR position;
	XMVECTOR at;
	XMVECTOR up;
	XMFLOAT4X4 view;
	XMFLOAT4X4 projection;

	FLOAT windowHeight;
	FLOAT windowWidth;

	FLOAT nearDepth;
	FLOAT farDepth;

	float zMoveSpeed;
	float yMoveSpeed;

	float camAcceleration;

	float rotationX, rotationY;
	
	float turnSpeed;
	
private:
	void ForwardMovement();
	void BackwardMovement();
	void Ascension();
	void Descension();
	void LeftTurn();
	void RightTurn();
	void UpwardTurn();
	void DownwardTurn();

	// Camera Movement method
	void Movement();
	void RecalculateCamera();

public:
	Camera(const UINT &windowHeight, const UINT &windowWidth);
	Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth);

	void Update();
	
	void SetWorldPosition(const XMFLOAT3& eyePos)							{ position = XMVectorSet(eyePos.x, eyePos.y, eyePos.z, 1); }
	void SetAt(const XMFLOAT3& atPos)										{ at = XMVectorSet(atPos.x, atPos.y, atPos.z, 1); }
	void SetViewMatrix(const XMFLOAT4X4& _view)								{ view = _view; }
	void SetProjectionMatrix(const XMFLOAT4X4& _projection)					{ projection = _projection; }

	
	XMFLOAT3 GetUp() const													{ return XMFLOAT3(up.m128_f32[0], up.m128_f32[1], up.m128_f32[2]); }
	XMFLOAT3 GetAt() const													{ return XMFLOAT3(at.m128_f32[0], at.m128_f32[1], at.m128_f32[2]); }
	XMFLOAT3 GetPosition() const											{ return XMFLOAT3(position.m128_f32[0], position.m128_f32[1], position.m128_f32[2]); }
	XMFLOAT3 GetWorldPosition() const										{ return XMFLOAT3(position.m128_f32[0], position.m128_f32[1], position.m128_f32[2]); }
	XMFLOAT4X4 GetViewMatrix() const										{ return view; }
	XMFLOAT4X4 GetProjectionMatrix() const									{ return projection; }
};

