#include "SpotLight.h"

SpotLight::SpotLight() { }

SpotLight::SpotLight(glm::vec3 color, float constant, float linear, float quadratic, float innerConeAngle, float outerConeAngle) :
	PointLight(color, constant, linear, quadratic), innerCone(innerConeAngle), outerCone(outerConeAngle) { }

void SpotLight::setShaderUniforms(Shader& shader, int index)
{
	std::string indexStr = std::to_string(index);
	shader.setVec3("spotLights[" + indexStr + "].pointLight.color", color);
	shader.setVec3("spotLights[" + indexStr + "].pointLight.position", position);
	shader.setFloat("spotLights[" + indexStr + "].pointLight.constant", constant);
	shader.setFloat("spotLights[" + indexStr + "].pointLight.linear", linear);
	shader.setFloat("spotLights[" + indexStr + "].pointLight.quadratic", quadratic);

	shader.setVec3("spotLights[" + indexStr + "].direction", glm::vec3(1.0f, 0.0f, 0.0f) * rotation); // Default (un-rotated) direction is forwards (negative x)
	shader.setFloat("spotLights[" + indexStr + "].innerCone", innerCone);
	shader.setFloat("spotLights[" + indexStr + "].outerCone", outerCone);
}
