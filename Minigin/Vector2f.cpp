#include "MiniginPCH.h"
#include "Vector2f.h"
#include <iomanip>
#include <SDL_stdinc.h>

//****************
//* CONSTRUCTORS *
//****************
sen::Vector2f::Vector2f()
	:x(0.0f)
	,y(0.0f)
{}
sen::Vector2f::Vector2f(float x, float y)
	:x(x)
	,y(y)
{}
sen::Vector2f::Vector2f(const sen::float2& from, const sen::float2 till)
	:x(till.x - from.x)
	,y(till.y - from.y)
{}
sen::Vector2f::Vector2f(const sen::float2& point)
	:x(point.x)
	,y(point.y)
{}

//**************
//* DESTRUCTOR *
//**************
sen::Vector2f::~Vector2f()
{}

//*************************
//* OPERATION OVERLOADERS *
//*************************
sen::Vector2f sen::Vector2f::operator-() const
{
	return Vector2f{ -x, -y };
}

sen::Vector2f sen::Vector2f::operator+ () const
{
	return Vector2f{ x, y };
}

sen::Vector2f& sen::Vector2f::operator*=(float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

sen::Vector2f& sen::Vector2f::operator/=(float rhs)
{
	*this *= 1 / rhs;
	return *this;
}

sen::Vector2f& sen::Vector2f::operator+=(const Vector2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

/**
 * \brief 
 * \param rhs 
 * \return 
 */
sen::Vector2f& sen::Vector2f::operator-=(const Vector2f& rhs)
{
	*this += -rhs;
	return *this;
}

//*************
//* FUNCTIONS *
//*************
sen::float2 sen::Vector2f::Tofloat2() const
{
	return sen::float2{ x, y };
}

bool sen::Vector2f::Equals(const Vector2f& other, float epsilon) const
{
	return (abs(x - other.x) < epsilon) && (abs(y - other.y) < epsilon);
}

float sen::Vector2f::DotProduct(const Vector2f& other) const
{
	return x * other.x + y * other.y;
}

float sen::Vector2f::CrossProduct(const Vector2f& other) const
{
	return x * other.y - y * other.x;
}

std::string sen::Vector2f::ToString() const
{
	std::stringstream buffer;

	buffer << std::fixed;
	buffer << std::setprecision(2);
	buffer << "Vector2f(" << x << ", " << y << ")";
	return buffer.str();
}

float sen::Vector2f::Norm() const
{
	return Length();
}

float sen::Vector2f::Length() const
{
	return sqrt(x * x + y * y);
}

float sen::Vector2f::SquaredLength() const
{
	return x * x + y * y;
}

float sen::Vector2f::AngleWith(const Vector2f& other) const
{
	float otherAngle{ other.y < 0 ? float(2 * M_PI) + atan2(other.y, other.x) : atan2(other.y, other.x) };
	float thisAngle{ y < 0 ? float(2 * M_PI) + atan2(y, x) : atan2(y, x) };
	return otherAngle - thisAngle;
}

sen::Vector2f sen::Vector2f::Normalized(float epsilon) const
{
	float length{ Length() };
	if (length < epsilon)
	{
		return Vector2f{ 0, 0 };
	}
	else
	{
		return Vector2f{ x / length, y / length };
	}
}

sen::Vector2f sen::Vector2f::Orthogonal() const
{
	return Vector2f{ -y, x };
}

sen::Vector2f sen::Vector2f::Reflect(const Vector2f& surfaceNormal) const
{
	return (*this) - 2 * (this->DotProduct(surfaceNormal) * surfaceNormal);
}

void sen::Vector2f::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}




//************************************
//* NON_MEMBER OPERATION OVERLOADERS *
//************************************
sen::Vector2f sen::operator*(float lhs, sen::Vector2f rhs)
{
	return rhs *= lhs;
}

sen::Vector2f sen::operator*(sen::Vector2f lhs, float rhs)
{
	return lhs *= rhs;
}

sen::Vector2f sen::operator/(sen::Vector2f lhs, float rhs)
{
	return lhs *= (1 / rhs);
}

sen::Vector2f sen::operator+(sen::Vector2f lhs, const sen::Vector2f& rhs)
{
	return lhs += rhs;
}

sen::Vector2f sen::operator-(sen::Vector2f lhs, const sen::Vector2f& rhs)
{
	return lhs += -rhs;
}

bool sen::operator==(const sen::Vector2f& lhs, const sen::Vector2f& rhs)
{
	return (lhs.Equals(rhs));
}

bool sen::operator!=(const sen::Vector2f& lhs, const sen::Vector2f& rhs)
{
	return !(lhs.Equals(rhs));
}

std::ostream& sen::operator<< (std::ostream& lhs, const sen::Vector2f& rhs)
{
	lhs << rhs.ToString();
	return lhs;
}
