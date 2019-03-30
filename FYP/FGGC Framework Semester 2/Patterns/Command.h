#pragma once
#include "../Physics/Particle.h"
#include "../Maths/kMaths.h"

class Command
{
public: 
	virtual ~Command() = default; 
	virtual void Execute(Particle& p) = 0;
};

class JumpCommand : public Command
{
public:
	void Execute(Particle& p) override { Jump(p); }
	
private:
	static void Jump(Particle &p)
	{
		p.AddForce(Vector3f(0.0f, powf(p.GetMass(), 2), 0.0f));
	}
};

class FlyCommand : public Command
{
public:
	void Execute(Particle& p) override { Fly(p); }

private:
	void Fly(Particle &p);
};