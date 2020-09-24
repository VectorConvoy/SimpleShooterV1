#pragma once
#ifndef _MATHHELPER_H
#define _MATHHELPER_H

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSquared() {
		return x * x + y * y;
	}

	float Magnitude()
	{
		return (float)sqrt(x * x + y * y);
	}

	Vector2 Normalized()
	{
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2& operator +=(const Vector2& rightHandSide)
	{
		x += rightHandSide.x;
		y += rightHandSide.y;

		return *this;
	}

	Vector2& operator -=(const Vector2* rightHandSide)
	{
		x -= rightHandSide->x;
		y -= rightHandSide->y;

		return *this;
	}

	Vector2 operator -() const
	{
		return Vector2(-x, -y);
	}
};

inline Vector2 operator +(const Vector2& leftHandSide, const Vector2& rightHandSide)
{
	return Vector2(leftHandSide.x + rightHandSide.x, leftHandSide.y + rightHandSide.y);
}

inline Vector2 operator -(const Vector2& leftHandSide, const Vector2& rightHandSide)
{
	return Vector2(leftHandSide.x - rightHandSide.x, leftHandSide.y - rightHandSide.y);
}

inline Vector2 operator *(const Vector2& leftHandSide, const float& rightHandSide)
{
	return Vector2(leftHandSide.x * rightHandSide, leftHandSide.y *rightHandSide);
}

inline Vector2 operator *(const float& leftHandSide, const Vector2& rightHandSide)
{
	return Vector2(leftHandSide * rightHandSide.x, leftHandSide * rightHandSide.y);
}

inline Vector2 operator /(const Vector2& leftHandSide, const float& rightHandSide)
{
	return Vector2(leftHandSide.x / rightHandSide, leftHandSide.y / rightHandSide);
}

inline Vector2 operator /(const float& leftHandSide, const Vector2& rightHandSide)
{
	return Vector2(leftHandSide / rightHandSide.x, leftHandSide / rightHandSide.y);
}



inline Vector2 RotateVector(Vector2& vec, float angle)
{
	float angleInRadians = (float)(angle * DEG_TO_RAD);

	return Vector2((float)(vec.x * cos(angleInRadians) - vec.y * sin(angleInRadians)), (float)(vec.x * sin(angleInRadians) + vec.y * cos(angleInRadians)));
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, -1.0f };
const Vector2 VEC2_DOWN = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };
const Vector2 VEC2_LEFT = { -1.0f, 0.0f };

#endif // !_MATHHELPER_H
