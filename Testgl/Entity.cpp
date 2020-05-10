#include "entity.h"

Entity::Entity() : 
	Entity(glm::vec3(0.0f)) { }

Entity::Entity(glm::vec3 position) : 
	Entity(position, glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) { }

Entity::Entity(glm::vec3 position, glm::vec3 rotation) : 
	Entity(position, rotation, glm::vec3(1.0f)) { }

Entity::Entity(glm::vec3 position, glm::quat rotation) : 
	Entity(position, rotation, glm::vec3(1.0f)) { }

Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : position(position), scale(scale)
{
	rotateAbsolute(glm::vec3(1.0f, 0.0f, 0.0f), rotation.x);
	rotateAbsolute(glm::vec3(0.0f, 1.0f, 0.0f), rotation.y);
	rotateAbsolute(glm::vec3(0.0f, 0.0f, 1.0f), rotation.z);
}

Entity::Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale) : 
	position(position), rotation(rotation), scale(scale) { }

Entity::~Entity()
{

}

void Entity::updateModelMatrix()
{
	// Translation * Rotation * Scale
	modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(1.0f), scale);
}

void Entity::rotate(glm::vec3 axis, float angle)
{
	rotation = glm::angleAxis(angle, axis) * rotation;
}

void Entity::rotateAbsolute(glm::vec3 axis, float angle)
{
	// Added rotation will not depend on initial rotation angle
	rotation = rotation * glm::angleAxis(angle, axis);
}
