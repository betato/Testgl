#pragma once
#include "Entity.h"
#include "TexturedModel.h"

class TexturedEntity : public Entity
{
public:
	TexturedEntity();
	TexturedEntity(TexturedModel* model);
	TexturedEntity(TexturedModel* model, glm::vec3 position);
	TexturedEntity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation);
	TexturedEntity(TexturedModel* model, glm::vec3 position, glm::quat rotation);
	TexturedEntity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	TexturedEntity(TexturedModel* model, glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	~TexturedEntity();

	TexturedModel* model;
};

