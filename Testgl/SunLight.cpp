#include "SunLight.h"

#include <glm/glm.hpp>

#include "Shader.h"

void SunLight::setShaderUniforms(Shader& shader)
{
	shader.setVec3("pointLight.color", color);
	shader.setVec3("pointLight.direction", rotation * glm::vec3(0.0f, 0.0f, -1.0f)); // Default (un-rotated) direction is down (negative z)
}
