#pragma once
#include "Vec3.h"

class Camera
{
public:
	static Camera* activeCamera;

	Vec3 position = Vec3(0,0,0);
	Vec3 viewDirection = Vec3(5, 5, 5);
	const Vec3 Up = Vec3(0, 1, 0);

	Camera();
	~Camera();

	void setActive();
	void update(); //temporary. Also called in CoreEngine.update();
};

