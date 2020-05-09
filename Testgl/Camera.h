#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	Camera(glm::vec3 position, glm::quat rotation, float fov);
	glm::mat4 getView();
	void updateDirection();

	float fov;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};
