#pragma once
#include "../base/renderer_object.h"
#include "text.h"

namespace munity
{	
	class ui : public renderer_object
	{
	protected:
		static unsigned int default_width;
		static unsigned int default_height;
	public:
		ui(unsigned int posx, unsigned int posy, unsigned int width, unsigned int height)
		 : renderer_object(glm::vec3(posx, posy, 0.0f)), width(width), height(height) {}

	protected:
		unsigned int width;
		unsigned int height;

		static glm::vec4	default_lineColor;
		static glm::vec4	default_fillColor;
		static glm::vec4	default_textColor;
		const  int radius = 5;

		~ui() = default;
	};
}
