#include "Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#define VERTEX_LOACTION 0
#define NORMAL_LOACTION 1

Model::Model()
{

}

Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	if (indexCount > 0)
		glDeleteBuffers(1, &EBO);
}

void Model::loadVertex(float* vertices, int vertexCount, int vertexSize, GLenum usage)
{
	this->vertexCount = vertexCount;
	// Create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * vertexSize, vertices, usage);
	// Load positions
	glVertexAttribPointer(VERTEX_LOACTION, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)0);
	glEnableVertexAttribArray(VERTEX_LOACTION);
}

void Model::loadVertexNormal(float* vertices, int vertexCount, int vertexSize, GLenum usage)
{
	// Create VAO nad load verticies
	loadVertex(vertices, vertexCount, vertexSize, usage);
	// Load normals
	glVertexAttribPointer(NORMAL_LOACTION, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(NORMAL_LOACTION);
}

void Model::loadIndices(unsigned int* indices, int indexCount, GLenum usage)
{
	// Call this method after adding texture coords or colors as it unbinds the VBO
	this->indexCount = indexCount;
	// Load indices
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, usage);
}

void Model::bind()
{
	glBindVertexArray(VAO);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Model::drawIndices()
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}


