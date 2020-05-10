#include "ColoredModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define COLOR_LOACTION 2

ColoredModel::ColoredModel()
{

}

ColoredModel::~ColoredModel()
{

}

void ColoredModel::loadVertexColor(float* vertices, int vertexCount, GLenum usage)
{
	// 3, 6=3+3
	Model::loadVertex(vertices, vertexCount, 6, usage);
	glVertexAttribPointer(COLOR_LOACTION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(COLOR_LOACTION);
}

void ColoredModel::loadVertexNormalColor(float* vertices, int vertexCount, GLenum usage)
{
	// 6=3+3, 9=3+3+3
	Model::loadVertexNormal(vertices, vertexCount, 9, usage);
	glVertexAttribPointer(COLOR_LOACTION, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(COLOR_LOACTION);
}
