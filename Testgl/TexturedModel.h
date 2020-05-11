#pragma once

#include "Model.h"

class TexturedModel : public Model
{
	public:
	TexturedModel();
	~TexturedModel();

	void loadVertexNormalTexture(float* vertices, int vertexCount, GLenum usage);
	void bind();

};
