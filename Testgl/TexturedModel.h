#pragma once
#include <glad/glad.h>

#include "Model.h"
#include "Shader.h"

class TexturedModel : public Model
{
	public:
	TexturedModel();
	~TexturedModel();

	enum TextureType
	{
		DIFFUSE = 0,
		SPECULAR = 1,
		NORMAL = 2,
		HEIGHT = 3
	};
	 
	void loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage);
	void loadTexture(const char* path, TextureType textureType);
	void bind(Shader& shader);

private:
	unsigned int textureID[4];
	bool textureLoaded[4]{0};

};
