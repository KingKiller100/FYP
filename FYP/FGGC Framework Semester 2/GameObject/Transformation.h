#pragma once
#include <DirectXMath.h>
#include "Maths/kMaths.h"

using namespace DirectX;

class Transformation
{
private:
	Vector3f _position;
	Vector3f _rotation;
	Vector3f _scale;

	XMFLOAT4X4 _world;
	Transformation * _parent;
public:
	Transformation();
	~Transformation();

	// Setters and Getters for position/rotation/scale/original position

	void SetPosition(const Vector3f &position)								{ _position = position; }
	void SetPosition(const float x, const float y, const float z)			{ _position.x = x; _position.y = y; _position.z = z; }
	Vector3f GetPosition() 													const { return _position; }
	XMMATRIX GetTranslationMatrix();

	void SetScale(const Vector3f& scale)									{ _scale = scale; }
	void SetScale(const float x, const float y, const float z)				{ _scale.x = x; _scale.y = y; _scale.z = z; }
	Vector3f GetScale() 													const { return _scale; }
	XMMATRIX GetScaleMatrix();

	void SetRotation(const Vector3f &rotation)								{ _rotation = rotation; }
	void SetRotation(const float x, const float y, const float z)			{ _rotation.x = x; _rotation.y = y; _rotation.z = z; }
	Vector3f GetRotation() 													const { return _rotation; }
	XMMATRIX GetRotationMatrix();

	XMMATRIX GetWorldMatrix()												const { return XMLoadFloat4x4(&_world); }
	void UpdateWorldMatrix();

	void SetParent(Transformation * parent)									{ _parent = parent; }
};	

