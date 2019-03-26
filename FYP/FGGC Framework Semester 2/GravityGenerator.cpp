#include "GravityGenerator.h"
#include "Particle.h"


GravityGenerator::GravityGenerator() : currentGravity(Vector3f(0, 9.81f, 0))
{
	realGravity = currentGravity;
}

GravityGenerator::GravityGenerator(const float g) : currentGravity(Vector3f(0, g, 0))
{
	realGravity = currentGravity;
}

GravityGenerator::~GravityGenerator()
= default;

void GravityGenerator::Update(Particle* p)
{
	p->AddForce(currentGravity * p->GetMass());
}