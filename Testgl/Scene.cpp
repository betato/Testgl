#include "Scene.h"

#include <algorithm>

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::load()
{
	entityShader.load("../Testgl/res/shader/entity.vert", "../Testgl/res/shader/entity.frag");
	lightSourceShader.load("../Testgl/res/shader/lightsource.vert", "../Testgl/res/shader/lightsource.frag");

	lightCubeModel.loadVertex(lightCubeVerticies, 8, 3, GL_STATIC_DRAW);
	lightCubeModel.loadIndices(lightCubeIndicies, 36, GL_STATIC_DRAW);
}

void Scene::addEntity(TexturedEntity entity)
{
	texturedEntities.insert(std::make_pair(entity.texture, entity));
}

void Scene::addEntity(ColoredEntity entity)
{
	coloredEntities.push_back(entity);
}

#define MAX_SUN_LIGHTS 4
#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

void Scene::draw()
{
	entityShader.use();

	// Lighting
	// TODO: Sort point lights and spot lights by distance and render the closet ones
	unsigned int numSunLights = std::min((int)sunLights.size(), MAX_SUN_LIGHTS);
	entityShader.setInt("numSunLights", numSunLights);
	for (size_t i = 0; i < numSunLights; i++)
	{
		sunLights[i].setShaderUniforms(entityShader, i);
	}

	unsigned int numPointLights = std::min((int)pointLights.size(), MAX_POINT_LIGHTS);
	entityShader.setInt("numPointLights", numPointLights);
	for (size_t i = 0; i < numPointLights; i++)
	{
		pointLights[i].setShaderUniforms(entityShader, i);
	}

	unsigned int numSpotLights = std::min((int)spotLights.size(), MAX_SPOT_LIGHTS);
	entityShader.setInt("numSpotLights", numSpotLights);
	for (size_t i = 0; i < numSpotLights; i++)
	{
		spotLights[i].setShaderUniforms(entityShader, i);
	}

	// Camera
	entityShader.setVec3("viewPos", camera.position);
	glm::mat4 projection(1.0f);
	projection = glm::perspective(glm::radians(camera.fov), (float)*screenWidth / (float)*screenHeight, 0.1f, 100.0f);
	entityShader.setMat4("projection", projection);
	entityShader.setMat4("view", camera.getView());

	// Entities
	Texture* currentTexture = nullptr;
	for (auto it = texturedEntities.begin(); it != texturedEntities.end(); it++)
	{
		TexturedEntity texturedEntity = it->second;
		if (texturedEntity.texture != currentTexture)
		{
			currentTexture = texturedEntity.texture;
			currentTexture->bind(entityShader);
		}
		texturedEntity.model->bind();
		texturedEntity.material->setShaderUniforms(entityShader);
		entityShader.setMat4("model", texturedEntity.entity.modelMatrix);
		texturedEntity.model->draw();
	}

	// Light Entities
	lightSourceShader.use();
	lightSourceShader.setMat4("projection", projection);
	lightSourceShader.setMat4("view", camera.getView());
	lightCubeModel.bind();
	for (auto it = pointLights.begin(); it != pointLights.end(); it++)
	{
		// Draw each point light as a cube
		lightSourceShader.setMat4("model", it->modelMatrix);
		lightSourceShader.setVec3("lightColor", it->color);
		lightCubeModel.drawIndices();
	}
}
