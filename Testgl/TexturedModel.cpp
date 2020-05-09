#include "TexturedModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

TexturedModel::TexturedModel()
{
	
}

TexturedModel::~TexturedModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &textureID);
}

void TexturedModel::loadVertexData(float* vertices, int vertexCount)
{
	// TODO:
	// Add support for index buffers

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 5, vertices, GL_STATIC_DRAW); // 5 floats per vertex (3 + 2 texture)
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	this->vertexCount = vertexCount;
}

void TexturedModel::loadTexture(const char* path)
{
	// TODO:
	// Move texture loading and storage somewhere else
	// Render all models with identical textures together

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
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void TexturedModel::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
