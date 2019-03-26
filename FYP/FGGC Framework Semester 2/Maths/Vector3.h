#pragma once
#include <algorithm>

template<class TP> // Type Precision
struct Vector3 final
{
	TP x, y, z;

	Vector3(const TP x, const TP y, const TP z) : x(x), y(y), z(z)
	{ /* Empty */}

	Vector3()
	{
		x = y = z = 0;
	}

	Vector3(const TP f)
	{
		x = y = z = f;
	}

	~Vector3() = default;

	// Restricts vector value to max value
	void Truncate(const float max);

	// Reassigns values to be positives
	void ToPositives();

	// Finds angle between two vectors in degrees/radians
	static TP AngleBetweenVectors(const Vector3& v, const Vector3& u, const bool inDegrees = false);

	// Outputs the normal between two vectors
	static auto CrossProduct(const Vector3& u, const Vector3& v) -> Vector3;

	// Normalizes a vector
	static Vector3 Normalize(const Vector3& v)										{ const float mag = Vector3::Magnitude(v); return mag != 0 ? v / mag : v; }

	// Pure length of the vector
	static TP MagnitudeSQ(const Vector3& v)											{ return (v.x * v.x) + (v.y * v.y) + (v.z * v.z); }

	// Square rooted length of the vector
	static TP Magnitude(const Vector3& v)											{ return std::sqrt(Vector3::MagnitudeSQ(v)); }
		
	// Produces the dot product
	static TP DotProduct(const Vector3& v, const Vector3& u)						{ return (u.x * v.x) + (u.y * v.y) + (u.z * v.z); }

	// Calculates distance between two 3D objects
	TP Distance(const Vector3 &v)													{ return Vector3::Magnitude(v - *this); }

	// Returns vector times by -1 - does not reassign values
	Vector3 ReverseVector()															{ return *this * -1; }

	// Sets all values of the vector to zero
	void Zero()																		{ *this = Vector3(); }

	TP& operator[](size_t index)													{ return *(reinterpret_cast<TP*>(this) + index); }

	// Overloads + operator to add two vectors objects
	Vector3 operator+(const Vector3& v) const										{ return Vector3(this->x + v.x, this->y + v.y, this->z + v.z); }

	// Overloads - operator to subtract two vectors objects
	Vector3 operator-(const Vector3& v) const										{ return Vector3(this->x - v.x, this->y - v.y, this->z - v.z); }

	// Overloads * operator to multiply a vector and float object
	Vector3 operator*(const TP f) const												{ return Vector3(this->x * f, this->y * f, this->z * f); }

	// Overloads * operator to multiply two vector objects
	Vector3 operator*(const Vector3& v) const										{ return Vector3(this->x * v.x, this->y * v.y, this->z * v.z); }

	// Overloads / operator to divide a vector and float object
	Vector3 operator/(const TP f) const												{ return Vector3(this->x / f, this->y / f, this->z / f); }
	
	// Overloads / operator to divide two vectors objects
	Vector3 operator/(const Vector3& v) const										{ return Vector3(this->x / v.x, this->y / v.y, this->z / v.z); }

	// Overloads = operator to make one vector axis values equal to another
	Vector3 &operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}
																					
	// bool operator == returns true if both Vector3D values are equal				
	bool operator==(const Vector3& v) const											{ return (this->x == v.x && this->y == v.y && this->z == v.z); }
																					
	// bool operator != returns true if both Vector3D values are NOT equal			
	bool operator!=(const Vector3& v) const											{ return !(*this == v); }

	// adds to current vector3 value
	Vector3& operator+=(const Vector3& v)
	{
		*this = *this + v;

		return *this;
	}

	// divides current vector3 value
	Vector3& operator-=(const Vector3& v)
	{
		*this = *this - v;

		return *this;
	}

	// divides current vector3 value and sets variable to it
	Vector3& operator/=(const Vector3& v)
	{
		*this = *this / v;

		return *this;
	}

	// divides current vector3 value by a float and sets variable to it
	Vector3& operator/=(const TP f)
	{
		*this = *this / f;

		return *this;
	}

	// multiplies current vector3 value and sets variable to it
	Vector3& operator*=(const Vector3& v)
	{
		*this = *this * v;

		return *this;
	}

	// multiply current vector3 value by a float and sets variable to it
	Vector3& operator*=(const TP f)
	{
		*this = *this * f;

		return *this;
	}
};

