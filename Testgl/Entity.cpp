#include "entity.h"

Entity::Entity() : Entity(glm::vec3(0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f))
{
	
}

Entity::Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

Entity::~Entity()
{

}

void Entity::updateModelMatrix()
{
	// Translation * Rotation * Scale
	model = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
}

void Entity::rotate(glm::vec3 axis, float angle)
{
	rotation = glm::angleAxis(angle, axis) * rotation;
}
