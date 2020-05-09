#pragma once
#include <glm/glm.hpp>
#include "Entity.h"

class Light : public Entity
{
public:
	Light();
	Light(glm::vec3 color);
	~Light();

	glm::vec3 color;
};

