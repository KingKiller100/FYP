#include "Particle.h"
#include <random>

Particle::Particle(Transformation * transform) : _transform(transform)
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	const std::uniform_real_distribution<float> distribution(0.001, 1);

	coefficientOfRestitution = distribution(generator);

	generalFriction = 0.98f;
	_radius = 0.5f;
	_mass = 1.0f;

	_velocity = _acceleration = netForce = Vector3f();

	isLaminar = true;
	isKillable = false;

	lifeTimer = -1;

	forcesMap.insert(std::pair<std::string, ForceGenerator*>("gravity", new GravityGenerator(-9.81f / 8)));
	forcesMap.insert(std::pair<std::string, ForceGenerator*>("laminar", new LaminarDragGenerator()));
}

Particle::~Particle()
{
	delete _transform;
	_transform = nullptr;

	for (auto && force : forcesMap)
	{
		delete force.second;
		force.second = nullptr;
	}

	forcesMap.clear();
}

void Particle::Update(const float t)
{
	if (_mass < 0)
		return;

	const auto dt = t > 1.f / 60.f ? 1.f / 60.f : t;

	UpdateNetForce();
	UpdateAccel();
	MoveParticle(dt);
	UpdateVelocity(dt);

	netForce.Zero();

	lifeTimer += dt;  
}

void Particle::AddForce(const Vector3f &f)
{
	netForce += f;
}

void Particle::AddGenerator(const std::string &id, ForceGenerator* fg)
{
	forcesMap.insert(std::pair<std::string, ForceGenerator*>(id, fg));
}

void Particle::UpdateNetForce()
{
	for (auto fg : forcesMap)
		fg.second->Update(this);
}

void Particle::MoveParticle(const float t) const
{
	Vector3f pos = _transform->GetPosition();	
	pos += _velocity * t + _acceleration * t * t * 0.5f;
	_transform->SetPosition(pos);
}

void Particle::UpdateVelocity(const float t)
{
	_velocity += _acceleration * t;
	_velocity *= generalFriction;
}

void Particle::UpdateAccel()
{
	_acceleration = netForce / _mass;
}

float Particle::CalculateTerminalVelocity() const
{
	const float airDensity = 1.225f;
	
	const float doubleWeight = 2 * _mass * GetGravityForceGenerator()->GetGravity();

	const float drag = GetLamDragForceGenerator()->GetDragCoefficient();

	const float airResistance = airDensity * powf(2 * _radius, 2) * drag;
	
	return sqrt(doubleWeight / airResistance);
}
