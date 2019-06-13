#include "Camera.h"
#include "Input.h"
#include "KeyCode.h"
#include "Time.h"
#include <iostream>

Camera* Camera::activeCamera = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setActive()
{
	activeCamera = this;
	
}

void Camera::update()
{
	
	if(Input::isKeyHeld(KeyCode::A))
	{
		this->position.y -= 1 * Time::deltaTime;
		std::cout << "X POSITION: " << this->position.x << std::endl;
	}
	else if (Input::isKeyHeld(KeyCode::W))
	{
		this->position.z += 1 * Time::deltaTime;
		std::cout << "z POSITION: " << this->position.z << std::endl;
	}
	else if (Input::isKeyHeld(KeyCode::S))
	{
		this->position.z -= 1 * Time::deltaTime;
		std::cout << "z POSITION: " << this->position.z << std::endl;
	}
	else if (Input::isKeyHeld(KeyCode::D))
	{
		this->position.y += 1 * Time::deltaTime;
		std::cout << "X POSITION: " << this->position.x << std::endl;
	}
}