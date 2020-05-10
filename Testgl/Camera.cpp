#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Camera(glm::vec3(), glm::vec3(), 45.0f) { }

Camera::Camera(glm::vec3 position, glm::quat rotation, float fov) : Entity(position, rotation, glm::vec3(1.0f)), fov(fov)
{
	updateDirection();
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(position, position + forward, up);
}

void Camera::updateDirection()
{
	forward = glm::vec3(1.0f, 0.0f, 0.0f) * rotation;
	right = glm::vec3(0.0f, 1.0f, 0.0f) * rotation;
	up = glm::vec3(0.0f, 0.0f, 1.0f) * rotation;
}
