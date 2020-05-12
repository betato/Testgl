#pragma once
#include "Light.h"
#include "Shader.h"
#include <glm/glm.hpp>

class PointLight : public Light
{
public:
	PointLight();
	PointLight(glm::vec3 color, float constant, float linear, float quadratic);
	virtual void setShaderUniforms(Shader& shader, int index) override;

	float constant;
	float linear;
	float quadratic;
};
