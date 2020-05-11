#include "TexturedModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include "Shader.h"

#define TEXTURE_COORD_LOACTION 2

TexturedModel::TexturedModel()
{
	
}

TexturedModel::~TexturedModel()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		if (textureLoaded[i])
			glDeleteTextures(1, &textureID[i]);
	}		
}

void TexturedModel::loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage)
{
	// Load verticies and normals
	Model::loadVertexNormal(vertices, vertexCount, 8, usage);
	// Load texture coords 6=3+3, 8=3+3+2
	glVertexAttribPointer(TEXTURE_COORD_LOACTION, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(TEXTURE_COORD_LOACTION);
}

void TexturedModel::loadTexture(const char* path, TextureType textureType)
{
	glGenTextures(1, &textureID[textureType]);
	glBindTexture(GL_TEXTURE_2D, textureID[textureType]);
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
		textureLoaded[textureType] = true;
	}
	else
	{
		std::cerr << "ERROR::TEXTURE::LOADING_FAILED" << std::endl;
	}
	stbi_image_free(image);
}

void TexturedModel::bind(Shader& shader)
{
	Model::bind();

	// Loop through diffuse, specular, normal, height
	const char* samplerNames[] = { "texDiffuse", "texSpecular", "texNormal", "texHeight" };
	for (unsigned int i = 0; i < 4; i++)
	{
		if (textureLoaded[i])
		{
			shader.setInt(samplerNames[i], i); // Point sampler2D to texture unit
			glActiveTexture(GL_TEXTURE0 + i); // Make new texture unit active to bind new texture
			glBindTexture(GL_TEXTURE_2D, textureID[i]); // Bind texture to unit
		}
	}
}
