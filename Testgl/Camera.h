#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 rotation, float fov);
	glm::mat4 getView();
	void updateDirection();

	glm::vec3 position;
	glm::vec3 rotation;
	float fov;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
};
