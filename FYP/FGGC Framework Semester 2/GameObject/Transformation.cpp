#include "Transformation.h"

Transformation::Transformation() : _parent(nullptr)
{
	_position = Vector3f();
	_rotation = Vector3f();
	_scale = Vector3f(1.0f, 1.0f, 1.0f);
}

Transformation::~Transformation()
= default;

// Calculate world matrix
XMMATRIX Transformation::GetTranslationMatrix() const
{
	XMMATRIX translation = XMMatrixTranslation(_position.x, _position.y, _position.z);
	return translation;
}

XMMATRIX Transformation::GetScaleMatrix() const
{
	XMMATRIX scale = XMMatrixScaling(_scale.x, _scale.y, _scale.z);
	return scale;
}

XMMATRIX Transformation::GetRotationMatrix() const
{
	XMMATRIX rotation = XMMatrixRotationX(_rotation.x) * XMMatrixRotationY(_rotation.y) * XMMatrixRotationZ(_rotation.z);
	return rotation;
}

void Transformation::UpdateWorldMatrix()
{
	XMStoreFloat4x4(&_world, GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix());

	if (_parent)
		XMStoreFloat4x4(&_world, this->GetWorldMatrix() * _parent->GetWorldMatrix());
}
