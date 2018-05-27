#pragma once
#include "SenStructs.h"
#include <ostream>

namespace sen
{
	class Vector2f
	{
	public:
		//Constructor
		Vector2f();
		Vector2f(float x, float y);
		Vector2f(const sen::float2& from, const sen::float2 till);
		Vector2f(const sen::float2& point);

		//Desctructor
		~Vector2f();

		//Operation Overloaders
		Vector2f operator-() const;
		Vector2f operator+() const;
		Vector2f& operator*=(float rhs);
		Vector2f& operator/=(float rhs);
		Vector2f& operator+=(const Vector2f& rhs);
		Vector2f& operator-=(const Vector2f& rhs);

		//Functions

		// Convert to Point2f	
		sen::float2 Tofloat2() const;

		// Are two vectors equal within a threshold?				
		// u.Equals(v)
		bool Equals(const Vector2f& other, float epsilon = 0.001f) const;

		// Convert to String 
		std::string	ToString() const;

		// DotProduct
		// float d = u.DotProduct(v);
		float DotProduct(const Vector2f& other) const;

		// CrossProduct 
		// float d = u.CrossProduct(v);
		float CrossProduct(const Vector2f& other) const;

		// Norm of a vector 
		// float l = v.Norm();
		float Norm() const;

		// Length of a vector: 
		// float l = v.Length();
		float Length() const;

		// Square Length of a vector.
		// Faster alternative for Length, sqrt is not executed. 
		float SquaredLength() const;

		// AngleWith returns the angle with another vector. 
		// float angle = u.AngleWith(v);
		float AngleWith(const Vector2f& other) const;


		// Returns normalized form of a vector
		// Vector2f n = v.Normalized();
		Vector2f Normalized(float epsilon = 0.001f) const;

		// Returns the orthogonal of the Vector2f
		// Vector2f w = v.Orthogonal();
		Vector2f Orthogonal() const;

		// Returns a vector that is the reflection of the Vector2f
		// surfaceNormal: represents the normal of the surface at the reflection point
		Vector2f Reflect(const Vector2f& surfaceNormal) const;

		// Sets the values of x and y
		void Set(float newX, float newY);

		float x;
		float y;
	};

	//Non-member Operation Overloaders
	Vector2f operator*(float lhs, Vector2f rhs);
	Vector2f operator*(Vector2f lhs, float rhs);

	Vector2f operator/(Vector2f lhs, float rhs);

	Vector2f operator+(Vector2f lhs, const Vector2f& rhs);
	Vector2f operator-(Vector2f lhs, const Vector2f& rhs);

	bool operator==(const Vector2f& lhs, const Vector2f& rhs);
	bool operator!=(const  Vector2f& lhs, const Vector2f& rhs);
	std::ostream& operator<< (std::ostream& lhs, const Vector2f& rhs);
}
