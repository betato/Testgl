#include "SpotLight.h"

SpotLight::SpotLight() { }

SpotLight::SpotLight(glm::vec3 color, float constant, float linear, float quadratic, float innerConeAngle, float outerConeAngle) :
	PointLight(color, constant, linear, quadratic), innerCone(innerConeAngle), outerCone(outerConeAngle) { }

void SpotLight::setShaderUniforms(Shader& shader)
{
	shader.setVec3("spotLight.pointLight.color", color);
	shader.setVec3("spotLight.pointLight.position", position);
	shader.setFloat("spotLight.pointLight.constant", constant);
	shader.setFloat("spotLight.pointLight.linear", linear);
	shader.setFloat("spotLight.pointLight.quadratic", quadratic);

	shader.setVec3("spotLight.direction", glm::vec3(1.0f, 0.0f, 0.0f) * rotation); // Default (un-rotated) direction is forwards (negative x)
	shader.setFloat("spotLight.innerCone", innerCone);
	shader.setFloat("spotLight.outerCone", outerCone);
}
