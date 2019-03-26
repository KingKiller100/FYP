#include "TurbulentDragGenerator.h"
#include "Particle.h"


TurbulentDragGenerator::TurbulentDragGenerator() : dragCoefficient(.7f), waterCurrentVel(Vector3f(0, 0, 5.0f))
{
}

TurbulentDragGenerator::~TurbulentDragGenerator()
= default;

void TurbulentDragGenerator::Update(Particle* p)
{
	if (!p->isLaminarOn())
	{
		// Calculates magnitude of velocity
		const auto _velMag = Vector3f::Magnitude(waterCurrentVel);

		// Calculates unit of vector of velocity
		const auto _unitVel = Vector3f::Normalize(waterCurrentVel);

		// Calculates drag Magnitude
		const double dragMag = dragCoefficient * _velMag * _velMag;

		// Calculate of x and y componenets of drag force
		const Vector3f dragForce = _unitVel * -dragMag;

		p->AddForce(dragForce);
	}
}
