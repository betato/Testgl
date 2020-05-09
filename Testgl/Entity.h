#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Entity
{
public:
	Entity();
	Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	~Entity();
	void updateModelMatrix();
	void rotate(glm::vec3 axis, float angle);

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 model;
};

