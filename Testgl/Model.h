#pragma once
#include <glad/glad.h>

class Model
{
public:
	Model();
	~Model();

	void bind();
	void draw();
	void drawIndices();

	void loadVertex(float* vertices, int vertexCount, int vertexSize, GLenum usage);
	void loadVertexNormal(float* vertices, int vertexCount, int vertexSize, GLenum usage);

	void loadIndices(unsigned int* indices, int indexCount, GLenum usage);

protected:
	int vertexCount;
	int indexCount = 0;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

};

