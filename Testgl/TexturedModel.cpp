#include "TexturedModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#define TEXTURE_COORD_LOACTION 2

TexturedModel::TexturedModel()
{
	
}

TexturedModel::~TexturedModel()
{
	
}

void TexturedModel::loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage)
{
	// Load verticies and normals
	Model::loadVertexNormal(vertices, vertexCount, 8, usage);
	// Load texture coords 6=3+3, 8=3+3+2
	glVertexAttribPointer(TEXTURE_COORD_LOACTION, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(TEXTURE_COORD_LOACTION);
}

void TexturedModel::bind()
{
	Model::bind();
}
