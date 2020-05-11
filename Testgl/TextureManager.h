#pragma once
#include <unordered_map>
#include "Texture.h"

class TextureManager
{
public:
	TextureManager(std::string basePath);
	~TextureManager();

	Texture* const load(std::string name);
	bool isLoaded(std::string name);
	Texture* const get(std::string name);

	std::unordered_map<std::string, Texture> textures;

private:
	std::string textureNames[4] = { "/diffuse.png", "/specular.png", "/normal.png", "/height.png" };
	std::string basePath;
	unsigned int loadTexture(const char* filePath);

};

