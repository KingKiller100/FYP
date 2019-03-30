#include "LaminarDragGenerator.h"
#include "../Particle.h"

LaminarDragGenerator::LaminarDragGenerator() : dragCoefficient(0.40f)
{
}

LaminarDragGenerator::LaminarDragGenerator(const float dc) : dragCoefficient(dc)
{
}

LaminarDragGenerator::~LaminarDragGenerator()
= default;

void LaminarDragGenerator::Update(Particle* p)
{
	if (p->isLaminarOn())
	{
		const Vector3f dragForce = p->GetVelocity() * -dragCoefficient;
		p->AddForce(dragForce);
	}
}
