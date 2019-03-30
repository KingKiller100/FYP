#pragma once
#include <map>
#include "../Maths/kMaths.h"
#include "../GameObject/Transformation.h"
#include "Forces/ForceGenerator.h"
#include "Forces/GravityGenerator.h"
#include "Forces/LaminarDragGenerator.h"

class Particle
{
private:
	Transformation* _transform;
	
	Vector3f _velocity;
	Vector3f _acceleration;
	Vector3f netForce;

	std::map<std::string, ForceGenerator*> forcesMap;

	float generalFriction;
	float _radius;
	float _mass;
	float coefficientOfRestitution;
	float maxSpeed = 55;

	float lifeTimer;

	bool isLaminar;
	bool isKillable;

private:
	void UpdateNetForce();
	void UpdateAccel();
	void MoveParticle(const float t) const;
	void UpdateVelocity(const float t);

public:
	Particle(Transformation* _transform);
	~Particle();
	
	// Transform Accessor Methods
	Transformation* getTransformation()													const { return _transform; }
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Radius Accessor Methods
	void SetRadius(const float r)														{ _radius = fabsf(r); }
	float GetRadius() 																	const { return _radius; }
	float GetDiameter()																	const { return GetRadius() * 2; }
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Velocity Accessor Methods
	void SetVelocity(const Vector3f v)													{ _velocity = v; }
	void SetVelocity(const float x, const float y, const float z)											{ _velocity.x = x, _velocity.y = y, _velocity.z = z; }
	float GetSpeed()																	const { return Vector3f::Magnitude(_velocity); }
	Vector3f GetVelocity()																const { return _velocity; }

	// Acceleration Accessor Methods
	void SetAcceleration(const Vector3f &a)												{ _acceleration = a; }
	void SetAcceleration(const float x, const float y, const float z)					{ _acceleration.x = x, _acceleration.y = y, _acceleration.z = z; }
	float GetAccelerationMagnitude()													const { return Vector3f::Magnitude(_acceleration); }
	Vector3f GetAcceleration()															const { return _acceleration; }

	// Sets whether object is laminar or not
	void SwitchLaminarOn(const bool l)													{ isLaminar = l; }
	bool isLaminarOn()																	const { return isLaminar; }

	// Mass Accessor Methods
	void SetMass(const float mass)														{ _mass = mass; }
	float GetMass()																		const { return _mass; }

	// Coefficient of Restitution Accessors
	float GetCoefficientOfRestitution()													const { return coefficientOfRestitution; }
	void SetCoefficientOfRestitution(const float cor)									{ if (cor >= 0 && cor <= 1) coefficientOfRestitution = cor; }
	
	// MaxSpeed Accessor Methods
	float GetMaxSpeed()																	const { return maxSpeed; }

	// Particle's life Accessor Methods
	float GetLifeTimer()																const{ return lifeTimer; }
	void ResetLifeTimer()																{ lifeTimer = 0; }

	// Sets whether particle should be reset or not
	bool GetIsKillable()																const { return isKillable; }
	void IsKillableOn(const bool k)														{ isKillable = k; }

	// Forces Map
	std::map<std::string, ForceGenerator*> GetForcesList() const						{ return forcesMap; }
	GravityGenerator* GetGravityForceGenerator() const									{ return dynamic_cast<GravityGenerator*>(forcesMap.at("gravity")); }
	LaminarDragGenerator* GetLamDragForceGenerator() const								{ return dynamic_cast<LaminarDragGenerator*>(forcesMap.at("laminar")); }
	
	// Terminal Velocity
	float CalculateTerminalVelocity() const;

	void AddForce(const Vector3f& f);
	void AddGenerator(const std::string &id, ForceGenerator* fg);

	void Update(const float t);
};

