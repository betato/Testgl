#include "PointLight.h"
#include "Shader.h"

PointLight::PointLight(glm::vec3 color, float constant, float linear, float quadratic) : 
	Light(color), constant(constant), linear(linear), quadratic(quadratic) { }

void PointLight::setShaderUniforms(Shader& shader)
{
	shader.setVec3("pointLight.color", color);
	shader.setVec3("pointLight.position", position);
	shader.setFloat("pointLight.constant", constant);
	shader.setFloat("pointLight.linear", linear);
	shader.setFloat("pointLight.quadratic", quadratic);
}
