#pragma once
#include "../../Maths/kMaths.h"

class Particle;

class ForceGenerator
{
public:
	virtual ~ForceGenerator() = default;
	virtual void Update(Particle* p) = 0;
};

