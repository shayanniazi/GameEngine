#pragma once

class Vec3
{
public:
	static const size_t dimensions = 3;

	float x, y, z;
	
	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec3& vec);
	~Vec3();
	
	void normalize();
	float magnitude();
	float dotProduct(const Vec3& vec);
	Vec3 crossProduct(const Vec3& vec);

	void operator =(const Vec3& vec);
	Vec3 operator +(const Vec3& vec);
	Vec3 operator +(float value);
	Vec3 operator -(const Vec3& vec);
	Vec3 operator -(float value);
	Vec3 operator /(float value);
	Vec3 operator *(const Vec3& vec);
	Vec3 operator *(float scalar);
	void operator +=(const Vec3& vec);
	void operator +=(float value);
	void operator -=(const Vec3& vec);
	void operator -=(float value);
	void operator /=(float scalar);
	void operator *=(float scalar);
};

