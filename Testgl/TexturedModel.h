#pragma once
#include <glad/glad.h>

#include "Model.h"

class TexturedModel : public Model
{
public:
	TexturedModel();
	~TexturedModel();

	void loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage);
	void loadTexture(const char* path);
	void bind();

	bool texturesLoaded = false;

private:
	unsigned int textureID;

};
