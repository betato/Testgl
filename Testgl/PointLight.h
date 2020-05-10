#pragma once
#include "Light.h"
#include "Shader.h"

class PointLight : public Light
{
public:
	using Light::Light;
	PointLight(glm::vec3 color, float constant, float linear, float quadratic);
	virtual void setShaderUniforms(Shader& shader) override;

	float constant;
	float linear;
	float quadratic;
};
