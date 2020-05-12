#include "PointLight.h"
#include "Shader.h"

PointLight::PointLight() { }

PointLight::PointLight(glm::vec3 color, float constant, float linear, float quadratic) : 
	Light(color), constant(constant), linear(linear), quadratic(quadratic) { }

void PointLight::setShaderUniforms(Shader& shader, int index)
{
	std::string indexStr = std::to_string(index);
	shader.setVec3("pointLights[" + indexStr + "].color", color);
	shader.setVec3("pointLights[" + indexStr + "].position", position);
	shader.setFloat("pointLights[" + indexStr + "].constant", constant);
	shader.setFloat("pointLights[" + indexStr + "].linear", linear);
	shader.setFloat("pointLights[" + indexStr + "].quadratic", quadratic);
}
