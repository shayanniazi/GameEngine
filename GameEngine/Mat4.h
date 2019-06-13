#pragma once

class Vec3;
class TransformComponent;
class Camera;

class Mat4
{
public:
	Mat4();
	Mat4(float matrix[4][4]);
	Mat4(const Mat4& matrix);
	~Mat4();

	Mat4 getModel(TransformComponent transform);
	Mat4 getView(Camera camera);
	Mat4 getTranslation(Vec3 position);
	Mat4 getScale(Vec3 scale);
	Mat4 getRotation(Vec3 orientation);
	Mat4 getProjection(float fov, float aspect_ratio, float zNear, float zFar);
	Mat4 getOrthographic(float left, float right, float bottom, float top, float near, float far);

	void operator = (const Mat4& matrix);
	void operator = (float matrix[4][4]);
	void operator = (float value);

	Mat4 operator * (const Mat4& matrix);
	Mat4 operator * (float value);

	Mat4 operator + (const Mat4& matrix);
	Mat4 operator + (float value);

	Mat4 operator - (const Mat4& matrix);
	Mat4 operator - (float value);

//private:
	//initialize to identity matrix4x4
	float matrix4x4[4][4] = 
	{
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
};