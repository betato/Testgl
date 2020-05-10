#include "TexturedModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#define TEXTURE_LOACTION 2

TexturedModel::TexturedModel()
{
	
}

TexturedModel::~TexturedModel()
{
	if (texturesLoaded)
		glDeleteTextures(1, &textureID);
}

void TexturedModel::loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage)
{
	// Load verticies and normals
	Model::loadVertexNormal(vertices, vertexCount, 8, usage);
	// Load texture coords 6=3+3, 8=3+3+2
	glVertexAttribPointer(TEXTURE_LOACTION, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(TEXTURE_LOACTION);
}

void TexturedModel::loadTexture(const char* path)
{
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
	unsigned char *image = stbi_load(path, &width, &height, &channels, 0);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "ERROR::TEXTURE::LOADING_FAILED" << std::endl;
	}
	stbi_image_free(image);
}

void TexturedModel::bind()
{
	Model::bind();
	glBindTexture(GL_TEXTURE_2D, textureID);
}
