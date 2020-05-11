#include "TextureManager.h"

#include <stb_image.h>
#include <iostream>

// Base path must end with a slash
TextureManager::TextureManager(std::string basePath) : basePath(basePath) { }

TextureManager::~TextureManager()
{
	std::unordered_map<std::string, Texture>::iterator it;
	for (it = textures.begin(); it != textures.end(); it++)
	{
		it->second.deleteTextures();
	}
}

Texture* const TextureManager::load(std::string name)
{
	bool anyTextureLoaded = false;
	unsigned int textureIDs[4]{ 0 };
	for (unsigned int i = 0; i < 4; i++)
	{
		std::string filePath = basePath + name + textureNames[i];
		std::ifstream file(filePath);
		if (file.good())
		{
			std::cout << "Loading " << filePath << std::endl;
			textureIDs[i] = loadTexture(filePath.c_str());
			if (textureIDs[i] > 0)
				anyTextureLoaded = true;
		}
	}
	if (!anyTextureLoaded)
	{
		std::cerr << "ERROR::TEXTURE::LOADING_GROUP_FAILED" << std::endl;
	}
	textures[name] = Texture(textureIDs);
	return &textures[name];
}

bool TextureManager::isLoaded(std::string name)
{
	return textures.count(name) > 0;
}

Texture* const TextureManager::get(std::string name)
{
	if (textures.count(name) == 0)
	{
		// Load texture if it is not yet loaded
		return load(name);
	}
	return &textures[name];
}

unsigned int TextureManager::loadTexture(const char* filePath)
{
	// Texture types:
	// DIFFUSE = 0
	// SPECULAR = 1
	// NORMAL = 2
	// HEIGHT = 3

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image and create texture
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(filePath, &width, &height, &channels, 0);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		textureID = 0; // Reset to no texture loaded
		std::cerr << "ERROR::TEXTURE::LOADING_FAILED" << std::endl;
	}
	stbi_image_free(image);
	return textureID;
}
