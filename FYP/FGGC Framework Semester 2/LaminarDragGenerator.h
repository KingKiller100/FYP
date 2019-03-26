#pragma once
#include "ForceGenerator.h"

class LaminarDragGenerator final : public ForceGenerator
{
public:
	LaminarDragGenerator();
	LaminarDragGenerator(const float dc);
	~LaminarDragGenerator();

	float GetDragCoefficient() const						{ return dragCoefficient; }
	void SetDragCoefficient(const float dg)					{ dragCoefficient = dg; }

	void Update(Particle* p) override;
	
private:
	float dragCoefficient;
};

