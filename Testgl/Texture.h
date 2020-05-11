#pragma once
#include "Model.h"
#include "Shader.h"

class Texture
{
public:
	Texture();
	Texture(unsigned int* textureIDs);
	void bind(Shader& shader);
	void deleteTextures();

private:
	unsigned int textureIDs[4];
	const char* samplerNames[4] = { "texDiffuse", "texSpecular", "texNormal", "texHeight" };
};

