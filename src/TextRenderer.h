#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

#include "glm/glm.hpp"
#include "SimpleGLShader.h"

#include "VBO.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    GLuint Advance;     // Horizontal offset to advance to next glyph
};

class TextRenderer {
public:
	// Generate 
    void Load(GLuint width, GLuint height);
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
protected:
    GLuint VAO;
	VBO vbo;
    std::map<GLchar, Character> Characters; 
	SimpleGLShader shader;
};

#endif 