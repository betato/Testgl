#pragma once
#include "PointLight.h"
#include <glm/glm.hpp>

class SpotLight : public PointLight
{
public:
	SpotLight();
	SpotLight(glm::vec3 color, float constant, float linear, float quadratic, float innerConeAngle, float outerConeAngle);
	virtual void setShaderUniforms(Shader& shader) override;

	float innerCone;
	float outerCone;
};

