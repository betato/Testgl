#include "Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include "Shader.h"

Texture::Texture() { }

Texture::Texture(unsigned int* textureIDs)
{
	this->textureIDs[0] = textureIDs[0];
	this->textureIDs[1] = textureIDs[1];
	this->textureIDs[2] = textureIDs[2];
	this->textureIDs[3] = textureIDs[3];
}

void Texture::bind(Shader & shader)
{
	// Loop through diffuse, specular, normal, height
	for (unsigned int i = 0; i < 4; i++)
	{
		shader.setInt(samplerNames[i], i); // Point sampler2D to texture unit (This probably doesn't need to be done every time)
		glActiveTexture(GL_TEXTURE0 + i); // Make new texture unit active to bind new texture
		glBindTexture(GL_TEXTURE_2D, textureIDs[i]); // Bind texture to unit (zero will unbind previous texture)
	}
}

void Texture::deleteTextures()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		if (textureIDs[i] != 0)
			glDeleteTextures(1, &textureIDs[i]);
	}
}
