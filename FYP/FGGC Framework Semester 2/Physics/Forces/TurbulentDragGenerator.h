#pragma once
#include "ForceGenerator.h"

class TurbulentDragGenerator final : public ForceGenerator
{
public:
	TurbulentDragGenerator();
	~TurbulentDragGenerator();

	Vector3f GetCurrentVelocity() const					{ return waterCurrentVel; }
	double GetDragCoefficient() const					{ return dragCoefficient; }

	void SetDragCoefficient(const double dg)			{ dragCoefficient = dg; }
	void SetCurrentVelocity(const Vector3f &wc)			{ waterCurrentVel = wc; }

	void Update(Particle* p) override;

private:
	double dragCoefficient;
	Vector3f waterCurrentVel;
};

