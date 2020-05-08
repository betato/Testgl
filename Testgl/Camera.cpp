#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Camera(glm::vec3(), glm::vec3(), 45.0f) { }

Camera::Camera(glm::vec3 position, glm::vec3 rotation, float fov)
{
	this->position = position;
	this->rotation = rotation;
	this->fov = fov;
	updateDirection();
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::updateDirection()
{
	// Calculate new front
	glm::vec3 front;
	front.x = cos(rotation.z) * cos(rotation.y);
	front.y = sin(rotation.y);
	front.z = sin(rotation.z) * cos(rotation.y);
	// Update front, right and up
	this->front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}
