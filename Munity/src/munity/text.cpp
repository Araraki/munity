#include <ft2build.h>
#include FT_FREETYPE_H
#pragma comment(lib, "freetype.lib") 

#include "text.h"

namespace munity
{
	std::string text::default_font = "res/fonts/arial.ttf";
	std::map<GLchar, Character> text::characters = std::map<GLchar, Character>();
	glm::vec4 text::default_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	void text::initialize()
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout << "Error::FreeType: Could not init FreeType Library" << std::endl;

		FT_Face face;
		if (FT_New_Face(ft, default_font.c_str(), 0, &face))
			std::cout << "Error::FreeType: Failed to load font" << std::endl;

		FT_Set_Pixel_Sizes(face, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Error::FreeType: Failed to load Glyph" << std::endl;
				continue;
			}

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
				face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
				GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character =
			{
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			characters.insert(std::pair<GLchar, Character>(c, character));
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	text::text(std::string content, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color) :
		renderer_object(position, rotation, scale),
		textShader("res/shaders/text.vert", "res/shaders/text.frag")
	{
		this->content = content;
		this->color = color;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void text::renderer()
	{
		renderer(textShader);
	}

	void text::renderer(shader& shader)
	{
		shader.use();
		//glUniform3f(glGetUniformLocation(shader.))
		shader.setVec4("texColor", color);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		float x = position.x;
		float y = position.y;
		for (std::string::const_iterator c = content.begin(); c != content.end(); ++c)
		{
			Character ch = characters[*c];

			GLfloat xpos = x + ch.bearing.x * scale.x;
			GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale.x;

			GLfloat w = ch.size.x * scale.x;
			GLfloat h = ch.size.y * scale.x;

			GLfloat vertices[6][4] =
			{
				{xpos,		ypos+h,	0.0f, 0.0f},
				{xpos,		ypos,	0.0f, 1.0f},
				{xpos+w,	ypos,	1.0f, 1.0f},

				{xpos,		ypos+h,	0.0f, 0.0f},
				{xpos+w,	ypos,	1.0f, 1.0f},
				{xpos+w,	ypos+h,	1.0f, 0.0f},
			};
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.advance >> 6)*scale.x;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
