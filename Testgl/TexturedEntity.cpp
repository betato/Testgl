#include "TexturedEntity.h"

TexturedEntity::TexturedEntity() { }
TexturedEntity::TexturedEntity(TexturedModel* model)
	{ this->model = model; }
TexturedEntity::TexturedEntity(TexturedModel* model, glm::vec3 position) :
	Entity(position) { this->model = model; }
TexturedEntity::TexturedEntity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation) :
	Entity(position, rotation) { this->model = model; }
TexturedEntity::TexturedEntity(TexturedModel* model, glm::vec3 position, glm::quat rotation) :
	Entity(position, rotation) { this->model = model; }
TexturedEntity::TexturedEntity(TexturedModel* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	Entity(position, rotation, scale) { this->model = model; }
TexturedEntity::TexturedEntity(TexturedModel* model, glm::vec3 position, glm::quat rotation, glm::vec3 scale) :
	Entity(position, rotation, scale) { this->model = model; }

TexturedEntity::~TexturedEntity()
{

}
