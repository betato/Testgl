#pragma once
class TexturedModel
{
public:
	TexturedModel();
	~TexturedModel();
	
	void loadVertexData(float* vertices, int vertexCount);
	void loadTexture(const char* path);
	void bind();
	void draw();

private:
	int vertexCount;

	unsigned int VBO;
	unsigned int VAO;
	unsigned int textureID;
};
