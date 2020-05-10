#pragma once
#include <glm/glm.hpp>
#include "Light.h"
#include "Shader.h"

class SunLight : public Light
{
public:
	using Light::Light;
	virtual void setShaderUniforms(Shader& shader) override;
};
