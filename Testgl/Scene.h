#pragma once
#include <map>
#include <vector>

#include "TexturedModel.h"
#include "Entity.h"
#include "Material.h"
#include "Shader.h"
#include "ColoredModel.h"
#include "Texture.h"
#include "Camera.h"

#include "PointLight.h"
#include "SunLight.h"
#include "SpotLight.h"

class Scene
{
public:
	Scene();
	~Scene();
	void load();

	void addEntity(TexturedEntity entity);
	void addEntity(ColoredEntity entity);
	void draw();

	PointLight pointLight;
	SunLight sunLight;
	SpotLight spotLight;
	Camera camera;

	int* screenWidth;
	int* screenHeight;

private:
	Shader entityShader;
	Shader lightSourceShader;

	Model lightCubeModel;
	float lightCubeVerticies[24] = {
		-0.125f, -0.125f, -0.125f,
		0.125f, -0.125f, -0.125f,
		0.125f,  0.125f, -0.125f,
		-0.125f,  0.125f, -0.125f,
		-0.125f, -0.125f,  0.125f,
		0.125f, -0.125f,  0.125f,
		0.125f,  0.125f,  0.125f,
		-0.125f,  0.125f,  0.125f
	};
	unsigned int lightCubeIndicies[36] = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	// TODO: Also sort by model for less model loads per draw
	std::multimap<Texture*, TexturedEntity> texturedEntities;
	std::vector<ColoredEntity> coloredEntities;
};
