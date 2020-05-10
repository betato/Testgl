#pragma once
#include <glm/glm.hpp>
#include "Entity.h"
#include "Shader.h"

class Light : public Entity
{
public:
	Light();
	Light(glm::vec3 color);
	virtual void setShaderUniforms(Shader& shader) = 0;

	glm::vec3 color;
};

