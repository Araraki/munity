#pragma once

#include <map>
#include <iostream>
#include "../base/renderer_object.h"

namespace munity
{
	struct Character
	{
		GLuint		textureID;
		glm::ivec2	size;
		glm::ivec2	bearing;
		GLuint		advance;
	};

	class text : public renderer_object
	{
	public:
		static std::string default_font;
		static std::map<GLchar, Character> characters;
		static glm::vec4 default_color;

		static void initialize();

		std::string content;
		glm::vec4 color;
		shader textShader;

		text(std::string content = "", glm::vec3 position = default_pos, glm::vec3 rotation = default_rot,
		     glm::vec3 scale = default_scl, glm::vec4 color = default_color);
		void renderer() override;
		void renderer(shader& shader) override;
	};
}
