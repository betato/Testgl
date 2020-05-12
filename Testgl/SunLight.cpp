#include "SunLight.h"

#include <glm/glm.hpp>

#include "Shader.h"

SunLight::SunLight() { }

SunLight::SunLight(glm::vec3 color) : Light(color) { }

void SunLight::setShaderUniforms(Shader& shader, int index)
{
	std::string indexStr = std::to_string(index);
	shader.setVec3("sunLights[" + indexStr + "].color", color);
	shader.setVec3("sunLights[" + indexStr + "].direction", glm::vec3(1.0f, 0.0f, 0.0f) * rotation); // Default (un-rotated) direction is forwards (negative x)
}
