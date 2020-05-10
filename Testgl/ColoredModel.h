#pragma once
#include <glad/glad.h>

#include "Model.h"

class ColoredModel : public Model
{
public:
	ColoredModel();
	~ColoredModel();

	void loadVertexColor(float* vertices, int vertexCount, GLenum usage);
	void loadVertexNormalColor(float* vertices, int vertexCount, GLenum usage);

};

