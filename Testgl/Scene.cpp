#include "Scene.h"

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

void Scene::draw()
{
	entityShader.use();

	// Lighting
	pointLight.setShaderUniforms(entityShader);
	sunLight.setShaderUniforms(entityShader);
	spotLight.setShaderUniforms(entityShader);

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
	lightSourceShader.setMat4("model", pointLight.modelMatrix);
	lightSourceShader.setVec3("lightColor", pointLight.color);
	lightCubeModel.bind();
	lightCubeModel.drawIndices();
}
