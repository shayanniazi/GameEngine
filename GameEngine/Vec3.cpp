#include "Vec3.h"
#include <iostream>
#include <cmath>

//initialize vector to (0,0,0)
Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//initialize vector to have coordinates similar to another vector
Vec3::Vec3(const Vec3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

Vec3::~Vec3(){}

void Vec3::normalize()
{
	float magnitude = this->magnitude();

	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

float Vec3::magnitude()
{
	float magnitude = sqrt((x*x) + (y*y) + (z*z));
	return magnitude;
}

float Vec3::dotProduct(const Vec3& vec)
{
	return ((x*vec.x) + (y*vec.y) + (z*vec.z));
}

Vec3 Vec3::crossProduct(const Vec3& vec)
{
	float x = (y*vec.z - z * vec.y);
	float y = (z*vec.x - x * vec.z);
	float z = (x*vec.y - y * vec.x);
	return Vec3(x, y, z);
}

void Vec3::operator = (const Vec3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vec3 Vec3::operator + (const Vec3& vec)
{
	float x = this->x + vec.x;
	float y = this->y + vec.y;
	float z = this->z + vec.z;
	return Vec3(x, y, z);
}

Vec3 Vec3::operator + (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	float z = this->z + value;
	return Vec3(x, y, z);
}

Vec3 Vec3::operator - (const Vec3& vec)
{
	float x = this->x + (-vec.x);
	float y = this->y + (-vec.y);
	float z = this->z + (-vec.z);
	return Vec3(x, y, z);
}

Vec3 Vec3::operator - (float value)
{
	float x = this->x - value;
	float y = this->y - value;
	float z = this->z - value;
	return Vec3(x, y, z);
}

Vec3 Vec3::operator / (float value)
{
	if (value == 0)
	{
		std::cout << "Cannot divide vector by 0, returning..." << std::endl;
		return Vec3(0, 0, 0);
	}

	float x = this->x / value;
	float y = this->y / value;
	float z = this->z / value;
	return Vec3(x, y, z);
}

Vec3 Vec3::operator * (float scalar)
{
	float x = this->x * scalar;
	float y = this->y * scalar;
	float z = this->z * scalar;
	return Vec3(x, y, z);
}

Vec3 Vec3::operator * (const Vec3& vec)
{
	float x = this->x * vec.x;
	float y = this->y * vec.y;
	float z = this->z * vec.z;
	return Vec3(x, y, z);
}

void Vec3::operator += (const Vec3& vec)
{
	float x = this->x + vec.x;
	float y = this->y + vec.y;
	float z = this->z + vec.z;
	*this = Vec3(x, y, z);
}

void Vec3::operator += (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	float z = this->z + value;
	*this = Vec3(x, y, z);
}

void Vec3::operator -= (const Vec3& vec)
{
	float x = this->x + (-vec.x);
	float y = this->y + (-vec.y);
	float z = this->z + (-vec.z);
	*this = Vec3(x, y, z);
}

void Vec3::operator -= (float value)
{
	float x = this->x + value;
	float y = this->y + value;
	float z = this->z + value;
	*this = Vec3(x, y, z);
}

void Vec3::operator *= (float scalar)
{
	float x = this->x * scalar;
	float y = this->y * scalar;
	float z = this->z * scalar;
	*this = Vec3(x, y, z);
}

void Vec3::operator /= (float value)
{
	if (value == 0)
	{
		std::cout << "Cannot divide vector by 0, returning..." << std::endl;
		return;
	}

	float x = this->x / value;
	float y = this->y / value;
	float z = this->z / value;
	*this = Vec3(x, y, z);
}