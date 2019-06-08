#pragma once
class Vec2
{
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	Vec2(const Vec2& vec);
	~Vec2();

	void normalize();
	float magnitude();
	float dotProduct(const Vec2& vec);
	float crossProduct(const Vec2& vec);

	void operator =(const Vec2& vec);
	Vec2 operator +(const Vec2& vec);
	Vec2 operator +(float value);
	Vec2 operator -(const Vec2& vec);
	Vec2 operator -(float value);
	Vec2 operator /(float value);
	Vec2 operator *(const Vec2& vec);
	Vec2 operator *(float scalar);
	void operator +=(const Vec2& vec);
	void operator +=(float value);
	void operator -=(const Vec2& vec);
	void operator -=(float value);
	void operator /=(float scalar);
	void operator *=(float scalar);
};

