#include "SunLight.h"

#include <glm/glm.hpp>

#include "Shader.h"

SunLight::SunLight() { }

SunLight::SunLight(glm::vec3 color) : Light(color) { }

void SunLight::setShaderUniforms(Shader& shader)
{
	shader.setVec3("sunLight.color", color);
	shader.setVec3("sunLight.direction", glm::vec3(1.0f, 0.0f, 0.0f) * rotation); // Default (un-rotated) direction is forwards (negative x)
}
