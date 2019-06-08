#include "Vec2.h"
#include <iostream>

//initialize vector to (0,0,0)
Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

//initialize vector to have coordinates similar to another vector
Vec2::Vec2(const Vec2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

Vec2::~Vec2() {}

void Vec2::normalize()
{
	float magnitude = this->magnitude();

	x = x / magnitude;
	y = y / magnitude;
}

float Vec2::magnitude()
{
	float magnitude = sqrt((x*x) + (y*y));
	return magnitude;
}

float Vec2::dotProduct(const Vec2& vec)
{
	return ((x*vec.x) + (y*vec.y));
}

float Vec2::crossProduct(const Vec2& vec)
{
	return (x*vec.y - y * vec.x);
}

void Vec2::operator = (const Vec2& vec)
{
	x = vec.x;
	y = vec.y;
}

Vec2 Vec2::operator + (const Vec2& vec)
{
	float x = this->x + vec.x;
	float y = this->y + vec.y;
	return Vec2(x, y);
}

Vec2 Vec2::operator + (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	return Vec2(x, y);
}

Vec2 Vec2::operator - (const Vec2& vec)
{
	float x = this->x + (-vec.x);
	float y = this->y + (-vec.y);
	return Vec2(x, y);
}

Vec2 Vec2::operator - (float value)
{
	float x = this->x - value;
	float y = this->y - value;
	return Vec2(x, y);
}

Vec2 Vec2::operator / (float value)
{
	if (value == 0)
	{
		std::cout << "Cannot divide vector by 0, returning..." << std::endl;
		return Vec2(0, 0);
	}

	float x = this->x / value;
	float y = this->y / value;
	return Vec2(x, y);
}

Vec2 Vec2::operator * (float scalar)
{
	float x = this->x * scalar;
	float y = this->y * scalar;
	return Vec2(x, y);
}

Vec2 Vec2::operator * (const Vec2& vec)
{
	float x = this->x * vec.x;
	float y = this->y * vec.y;
	return Vec2(x, y);
}

void Vec2::operator += (const Vec2& vec)
{
	float x = this->x + vec.x;
	float y = this->y + vec.y;
	*this = Vec2(x, y);
}

void Vec2::operator += (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	*this = Vec2(x, y);
}

void Vec2::operator -= (const Vec2& vec)
{
	float x = this->x + (-vec.x);
	float y = this->y + (-vec.y);
	*this = Vec2(x, y);
}

void Vec2::operator -= (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	*this = Vec2(x, y);
}

void Vec2::operator *= (float scalar)
{
	float x = this->x * scalar;
	float y = this->y * scalar;
	*this = Vec2(x, y);
}

void Vec2::operator /= (float value)
{
	if (value == 0)
	{
		std::cout << "Cannot divide vector by 0, returning..." << std::endl;
		return;
	}

	float x = this->x / value;
	float y = this->y / value;
	*this = Vec2(x, y);
}