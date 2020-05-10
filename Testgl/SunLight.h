#pragma once
#include <glm/glm.hpp>
#include "Light.h"
#include "Shader.h"

class SunLight : public Light
{
public:
	SunLight();
	SunLight(glm::vec3 color);
	virtual void setShaderUniforms(Shader& shader) override;
};
