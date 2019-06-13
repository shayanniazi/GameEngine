#define _USE_MATH_DEFINES
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0f)

#include "Mat4.h"
#include "Vec3.h"
#include "TransformComponent.h"
#include <math.h>
#include "Camera.h"

Mat4::Mat4() {}
Mat4::~Mat4() {}

Mat4::Mat4(float matrix[4][4])
{
	*this = matrix;
}

Mat4::Mat4(const Mat4& matrix)
{
	*this = matrix;
}

Mat4 Mat4::getProjection(float fov, float aspect_ratio, float zNear, float zFar)
{
	float matrix[4][4];

	float tan_fov_by2 = tan(fov / 2);
	float zRange = zNear - zFar;

	matrix[0][0] = 1.0f / (tan_fov_by2 * aspect_ratio); 	matrix[0][1] = 0;					matrix[0][2] = 0;							matrix[0][3] = 0;
	matrix[1][0] = 0; 										matrix[1][1] = 1.0f / tan_fov_by2;	matrix[1][2] = 0;							matrix[1][3] = 0;
	matrix[2][0] = 0; 										matrix[2][1] = 0;					matrix[2][2] = (-zNear - zFar) / zRange;	matrix[2][3] = 2 * zFar * zNear / zRange;
	matrix[3][0] = 0; 										matrix[3][1] = 0;					matrix[3][2] = 1;							matrix[3][3] = 0;

	return Mat4(matrix);
}

Mat4 Mat4::getOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	float matrix[4][4];

	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	matrix[0][0] = width; 		matrix[0][1] = 0;			matrix[0][2] = 9;			matrix[0][3] = left;
	matrix[1][0] = 0; 			matrix[1][1] = height;	    matrix[1][2] = 9;			matrix[1][3] = bottom;
	matrix[2][0] = 0;			matrix[2][1] = 0;			matrix[2][2] = depth;		matrix[2][3] = near;
	matrix[3][0] = 0; 			matrix[3][1] = 0;			matrix[3][2] = 0;			matrix[3][3] = 1;

	return Mat4(matrix);
}

Mat4 Mat4::getTranslation(Vec3 position)
{
	float matrix[4][4];

	matrix[0][0] = 1; 	matrix[0][1] = 0;	matrix[0][2] = 0;	matrix[0][3] = position.x;
	matrix[1][0] = 0; 	matrix[1][1] = 1;	matrix[1][2] = 0;	matrix[1][3] = position.y;
	matrix[2][0] = 0; 	matrix[2][1] = 0;	matrix[2][2] = 1;	matrix[2][3] = position.z;
	matrix[3][0] = 0; 	matrix[3][1] = 0;	matrix[3][2] = 0;	matrix[3][3] = 1;

	return Mat4(matrix);
}

Mat4 Mat4::getScale(Vec3 scale)
{
	float matrix[4][4];

	matrix[0][0] = scale.x; 	matrix[0][1] = 0;			matrix[0][2] = 0;			matrix[0][3] = 0;
	matrix[1][0] = 0;			matrix[1][1] = scale.y;		matrix[1][2] = 0;			matrix[1][3] = 0;
	matrix[2][0] = 0; 			matrix[2][1] = 0;			matrix[2][2] = scale.z;		matrix[2][3] = 0;
	matrix[3][0] = 0; 			matrix[3][1] = 0;			matrix[3][2] = 0;			matrix[3][3] = 1;

	return Mat4(matrix);
}

Mat4 Mat4::getRotation(Vec3 orientation)
{
	//initialized to identity matrices by default
	Mat4 rx;
	Mat4 ry;
	Mat4 rz;

	//converting angle from degrees to radians then calculating cosine and sine functions
	float xAngle = degToRad(orientation.x);
	float yAngle = degToRad(orientation.y);
	float zAngle = degToRad(orientation.z);

	float sinX = sin(xAngle);
	float sinY = sin(yAngle);
	float sinZ = sin(zAngle);
				 
	float cosX = cos(xAngle);
	float cosY = cos(yAngle);
	float cosZ = cos(zAngle);

	rx.matrix4x4[0][0] = 1; 		rx.matrix4x4[0][1] = 0;			rx.matrix4x4[0][2] = 0;			rx.matrix4x4[0][3] = 0;
	rx.matrix4x4[1][0] = 0; 		rx.matrix4x4[1][1] = cosX;		rx.matrix4x4[1][2] = -(sinX);	rx.matrix4x4[1][3] = 0;
	rx.matrix4x4[2][0] = 0; 		rx.matrix4x4[2][1] = sinX;		rx.matrix4x4[2][2] = cosX;		rx.matrix4x4[2][3] = 0;
	rx.matrix4x4[3][0] = 0; 		rx.matrix4x4[3][1] = 0;			rx.matrix4x4[3][2] = 0;			rx.matrix4x4[3][3] = 1;

	ry.matrix4x4[0][0] = cosY; 		ry.matrix4x4[0][1] = 0;			ry.matrix4x4[0][2] = sinY;		ry.matrix4x4[0][3] = 0;
	ry.matrix4x4[1][0] = 0; 		ry.matrix4x4[1][1] = 1;			ry.matrix4x4[1][2] = 0;			ry.matrix4x4[1][3] = 0;
	ry.matrix4x4[2][0] = -(sinY); 	ry.matrix4x4[2][1] = 0;			ry.matrix4x4[2][2] = cosY;		ry.matrix4x4[2][3] = 0;
	ry.matrix4x4[3][0] = 0; 		ry.matrix4x4[3][1] = 0;			ry.matrix4x4[3][2] = 0;			ry.matrix4x4[3][3] = 1;

	rz.matrix4x4[0][0] = cosZ; 		rz.matrix4x4[0][1] = -(sinZ);	rz.matrix4x4[0][2] = 0;			rz.matrix4x4[0][3] = 0;
	rz.matrix4x4[1][0] = sinZ; 		rz.matrix4x4[1][1] = cosZ;		rz.matrix4x4[1][2] = 0;			rz.matrix4x4[1][3] = 0;
	rz.matrix4x4[2][0] = 0; 		rz.matrix4x4[2][1] = 0;			rz.matrix4x4[2][2] = 1;			rz.matrix4x4[2][3] = 0;
	rz.matrix4x4[3][0] = 0; 		rz.matrix4x4[3][1] = 0;			rz.matrix4x4[3][2] = 0;			rz.matrix4x4[3][3] = 1;

	return (rx*ry*rz);
}

//computes and returns model matrix
Mat4 Mat4::getModel(TransformComponent transform)
{
	return getTranslation(transform.position) * getRotation(transform.orientation) * getScale(transform.scale);
	//return (getScale(transform.scale) * getRotation(transform.orientation) * getTranslation(transform.position));
}

Mat4 Mat4::getView(Camera camera)
{
	float matrix[4][4];

	Vec3 camDir = camera.viewDirection;
	camDir.normalize();
	Vec3 rightAxis = camera.Up;
	rightAxis = rightAxis.crossProduct(camera.viewDirection);
	rightAxis.normalize();
	Vec3 upAxis = camDir.crossProduct(rightAxis);

	matrix[0][0] = rightAxis.x;	    matrix[0][1] = rightAxis.y;		matrix[0][2] = rightAxis.z;		matrix[0][3] = 0.0f;
	matrix[1][0] = upAxis.x;		matrix[1][1] = upAxis.y;		matrix[1][2] = upAxis.z;		matrix[1][3] = 0.0f;
	matrix[2][0] = camDir.x;		matrix[2][1] = camDir.y;		matrix[2][2] = camDir.z;		matrix[2][3] = 0.0f;
	matrix[3][0] = 0.0f;		    matrix[3][1] = 0.0f;			matrix[3][2] = 0.0f;			matrix[3][3] = 1.0f;

	Mat4 camRotation(matrix);
	Vec3 invertedCamPos(-camera.position.x, -camera.position.y, -camera.position.z);
	Mat4 camTranslation = camTranslation.getTranslation(invertedCamPos);

	return camRotation * camTranslation;
}

void Mat4::operator = (const Mat4& matrix)
{
	matrix4x4[0][0] = matrix.matrix4x4[0][0]; 	matrix4x4[0][1] = matrix.matrix4x4[0][1];  matrix4x4[0][2] = matrix.matrix4x4[0][2];  matrix4x4[0][3] = matrix.matrix4x4[0][3];
	matrix4x4[1][0] = matrix.matrix4x4[1][0];	matrix4x4[1][1] = matrix.matrix4x4[1][1];  matrix4x4[1][2] = matrix.matrix4x4[1][2];  matrix4x4[1][3] = matrix.matrix4x4[1][3];
	matrix4x4[2][0] = matrix.matrix4x4[2][0];	matrix4x4[2][1] = matrix.matrix4x4[2][1];  matrix4x4[2][2] = matrix.matrix4x4[2][2];  matrix4x4[2][3] = matrix.matrix4x4[2][3];
	matrix4x4[3][0] = matrix.matrix4x4[3][0];	matrix4x4[3][1] = matrix.matrix4x4[3][1];  matrix4x4[3][2] = matrix.matrix4x4[3][2];  matrix4x4[3][3] = matrix.matrix4x4[3][3];
}

void Mat4::operator = (float matrix[4][4])
{
	matrix4x4[0][0] = matrix[0][0]; matrix4x4[0][1] = matrix[0][1];  matrix4x4[0][2] = matrix[0][2];  matrix4x4[0][3] = matrix[0][3];
	matrix4x4[1][0] = matrix[1][0];	matrix4x4[1][1] = matrix[1][1];  matrix4x4[1][2] = matrix[1][2];  matrix4x4[1][3] = matrix[1][3];
	matrix4x4[2][0] = matrix[2][0];	matrix4x4[2][1] = matrix[2][1];  matrix4x4[2][2] = matrix[2][2];  matrix4x4[2][3] = matrix[2][3];
	matrix4x4[3][0] = matrix[3][0];	matrix4x4[3][1] = matrix[3][1];  matrix4x4[3][2] = matrix[3][2];  matrix4x4[3][3] = matrix[3][3];
}

void Mat4::operator = (float value)
{
	matrix4x4[0][0] = value; 	matrix4x4[0][1] = value;  matrix4x4[0][2] = value;  matrix4x4[0][3] = value;
	matrix4x4[1][0] = value;	matrix4x4[1][1] = value;  matrix4x4[1][2] = value;  matrix4x4[1][3] = value;
	matrix4x4[2][0] = value;	matrix4x4[2][1] = value;  matrix4x4[2][2] = value;  matrix4x4[2][3] = value;
	matrix4x4[3][0] = value;	matrix4x4[3][1] = value;  matrix4x4[3][2] = value;  matrix4x4[3][3] = value;
}

Mat4 Mat4::operator * (const Mat4& matrix)
{
	float newMatrix[4][4];

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
				newMatrix[row][col] =   matrix4x4[row][0] * matrix.matrix4x4[0][col] +
				matrix4x4[row][1] * matrix.matrix4x4[1][col] +
				matrix4x4[row][2] * matrix.matrix4x4[2][col] +
				matrix4x4[row][3] * matrix.matrix4x4[3][col];
		}
	}

	return Mat4(newMatrix);
}

Mat4 Mat4::operator * (float value)
{
	float newMatrix[4][4];

	newMatrix[0][0] = matrix4x4[0][0] * value; newMatrix[0][1] = matrix4x4[0][1] * value;  newMatrix[0][2] = matrix4x4[0][2] * value; newMatrix[0][3] = matrix4x4[0][3] * value;
	newMatrix[1][0] = matrix4x4[1][0] * value; newMatrix[1][1] = matrix4x4[1][1] * value;  newMatrix[1][2] = matrix4x4[1][2] * value; newMatrix[1][3] = matrix4x4[1][3] * value;
	newMatrix[2][0] = matrix4x4[2][0] * value; newMatrix[2][1] = matrix4x4[2][1] * value;  newMatrix[2][2] = matrix4x4[2][2] * value; newMatrix[2][3] = matrix4x4[2][3] * value;
	newMatrix[3][0] = matrix4x4[3][0] * value; newMatrix[3][1] = matrix4x4[3][1] * value;  newMatrix[3][2] = matrix4x4[3][2] * value; newMatrix[3][3] = matrix4x4[3][3] * value;

	return Mat4(newMatrix);
}

Mat4 Mat4::operator - (const Mat4& matrix)
{
	float newMatrix[4][4];

	newMatrix[0][0] = matrix4x4[0][0] - matrix.matrix4x4[0][0]; newMatrix[0][1] = matrix4x4[0][1] - matrix.matrix4x4[0][1];  newMatrix[0][2] = matrix4x4[0][2] - matrix.matrix4x4[0][2]; newMatrix[0][3] = matrix4x4[0][3] - matrix.matrix4x4[0][3];
	newMatrix[1][0] = matrix4x4[1][0] - matrix.matrix4x4[1][0];	newMatrix[1][1] = matrix4x4[1][1] - matrix.matrix4x4[1][1];  newMatrix[1][2] = matrix4x4[1][2] - matrix.matrix4x4[1][2]; newMatrix[1][3] = matrix4x4[1][3] - matrix.matrix4x4[1][3];
	newMatrix[2][0] = matrix4x4[2][0] - matrix.matrix4x4[2][0];	newMatrix[2][1] = matrix4x4[2][1] - matrix.matrix4x4[2][1];  newMatrix[2][2] = matrix4x4[2][2] - matrix.matrix4x4[2][2]; newMatrix[2][3] = matrix4x4[2][3] - matrix.matrix4x4[2][3];
	newMatrix[3][0] = matrix4x4[3][0] - matrix.matrix4x4[3][0];	newMatrix[3][1] = matrix4x4[3][1] - matrix.matrix4x4[3][1];  newMatrix[3][2] = matrix4x4[3][2] - matrix.matrix4x4[3][2]; newMatrix[3][3] = matrix4x4[3][3] - matrix.matrix4x4[3][3];

	return Mat4(newMatrix);
}

Mat4 Mat4::operator - (float value)
{
	float newMatrix[4][4];

	newMatrix[0][0] = matrix4x4[0][0] - value;  newMatrix[0][1] = matrix4x4[0][1] - value;  newMatrix[0][2] = matrix4x4[0][2] - value; newMatrix[0][3] = matrix4x4[0][3] - value;
	newMatrix[1][0] = matrix4x4[1][0] - value;	newMatrix[1][1] = matrix4x4[1][1] - value;  newMatrix[1][2] = matrix4x4[1][2] - value; newMatrix[1][3] = matrix4x4[1][3] - value;
	newMatrix[2][0] = matrix4x4[2][0] - value;	newMatrix[2][1] = matrix4x4[2][1] - value;  newMatrix[2][2] = matrix4x4[2][2] - value; newMatrix[2][3] = matrix4x4[2][3] - value;
	newMatrix[3][0] = matrix4x4[3][0] - value;	newMatrix[3][1] = matrix4x4[3][1] - value;  newMatrix[3][2] = matrix4x4[3][2] - value; newMatrix[3][3] = matrix4x4[3][3] - value;

	return Mat4(newMatrix);
}

Mat4 Mat4::operator + (const Mat4& matrix)
{
	float newMatrix[4][4];

	newMatrix[0][0] = matrix4x4[0][0] + matrix.matrix4x4[0][0]; newMatrix[0][1] = matrix4x4[0][1] + matrix.matrix4x4[0][1];  newMatrix[0][2] = matrix4x4[0][2] + matrix.matrix4x4[0][2]; newMatrix[0][3] = matrix4x4[0][3] + matrix.matrix4x4[0][3];
	newMatrix[1][0] = matrix4x4[1][0] + matrix.matrix4x4[1][0];	newMatrix[1][1] = matrix4x4[1][1] + matrix.matrix4x4[1][1];  newMatrix[1][2] = matrix4x4[1][2] + matrix.matrix4x4[1][2]; newMatrix[1][3] = matrix4x4[1][3] + matrix.matrix4x4[1][3];
	newMatrix[2][0] = matrix4x4[2][0] + matrix.matrix4x4[2][0];	newMatrix[2][1] = matrix4x4[2][1] + matrix.matrix4x4[2][1];  newMatrix[2][2] = matrix4x4[2][2] + matrix.matrix4x4[2][2]; newMatrix[2][3] = matrix4x4[2][3] + matrix.matrix4x4[2][3];
	newMatrix[3][0] = matrix4x4[3][0] + matrix.matrix4x4[3][0];	newMatrix[3][1] = matrix4x4[3][1] + matrix.matrix4x4[3][1];  newMatrix[3][2] = matrix4x4[3][2] + matrix.matrix4x4[3][2]; newMatrix[3][3] = matrix4x4[3][3] + matrix.matrix4x4[3][3];

	return Mat4(newMatrix);
}

Mat4 Mat4::operator + (float value)
{
	float newMatrix[4][4];

	newMatrix[0][0] = matrix4x4[0][0] + value;  newMatrix[0][1] = matrix4x4[0][1] + value;  newMatrix[0][2] = matrix4x4[0][2] + value; newMatrix[0][3] = matrix4x4[0][3] + value;
	newMatrix[1][0] = matrix4x4[1][0] + value;	newMatrix[1][1] = matrix4x4[1][1] + value;  newMatrix[1][2] = matrix4x4[1][2] + value; newMatrix[1][3] = matrix4x4[1][3] + value;
	newMatrix[2][0] = matrix4x4[2][0] + value;	newMatrix[2][1] = matrix4x4[2][1] + value;  newMatrix[2][2] = matrix4x4[2][2] + value; newMatrix[2][3] = matrix4x4[2][3] + value;
	newMatrix[3][0] = matrix4x4[3][0] + value;	newMatrix[3][1] = matrix4x4[3][1] + value;  newMatrix[3][2] = matrix4x4[3][2] + value; newMatrix[3][3] = matrix4x4[3][3] + value;

	return Mat4(newMatrix);
}