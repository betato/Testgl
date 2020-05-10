#pragma once
#include <glm/glm.hpp>

#include "Shader.h"

struct Material
{
	// TODO: Add support for transparent materials

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shine;

	Material() { }

	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shine) :
		ambient(ambient), diffuse(diffuse), specular(specular), shine(shine) { }

	void setShaderUniforms(Shader& shader)
	{
		shader.setVec3("material.ambient", ambient);
		shader.setVec3("material.diffuse", diffuse);
		shader.setVec3("material.specular", specular);
		shader.setFloat("material.shine", shine);
	}
};