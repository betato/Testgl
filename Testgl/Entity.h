#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Entity
{
public:
	Entity();
	Entity(glm::vec3 position);
	Entity(glm::vec3 position, glm::vec3 rotation);
	Entity(glm::vec3 position, glm::quat rotation);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	~Entity();
	void updateModelMatrix();
	void rotate(glm::vec3 axis, float angle);
	void rotateAbsolute(glm::vec3 axis, float angle);

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 modelMatrix;
};

