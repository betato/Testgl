#pragma once

#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"

class FontManager
{
public:
	FontManager();
	~FontManager();
	void loadFont(const char* fontPath);
	void drawText(std::string text, float x, float y, float scale);
	
	struct Character {
		unsigned int textureID;  // ID of glyph texture
		glm::ivec2   size;       // Size of glyph
		glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
		unsigned int advance;    // Offset to advance to next glyph
	};
	
private:
	std::map<char, Character> characters;
	unsigned int VAO, VBO;
	Shader* shader;
};

