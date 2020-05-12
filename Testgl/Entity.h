#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Texture.h"
#include "TexturedModel.h"
#include "Material.h"
#include "ColoredModel.h"

class Entity
{
public:
	Entity();
	Entity(glm::vec3 position);
	Entity(glm::vec3 position, glm::vec3 rotation);
	Entity(glm::vec3 position, glm::quat rotation);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	~Entity();
	void updateModelMatrix();
	void rotate(glm::vec3 axis, float angle);
	void rotateAbsolute(glm::vec3 axis, float angle);

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::mat4 modelMatrix;
};

struct TexturedEntity
{
	//TexturedEntity() { }
	TexturedEntity(Texture* texture, TexturedModel* model, Material* material, Entity entity) :
		texture(texture), model(model), material(material), entity(entity) { }
	Texture* texture;
	TexturedModel* model;
	Material* material;
	Entity entity;
};

struct ColoredEntity
{
	//ColoredEntity() { }
	ColoredEntity(ColoredModel model, Material* material, Entity entity) :
		entity(entity), material(material), model(model) { }
	ColoredModel model;
	Material* material;
	Entity entity;
};

