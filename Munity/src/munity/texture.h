#pragma once

#include <glad/glad.h>
#include <string>

namespace munity
{
	class texture
	{
	public:
		unsigned int ID;
		int width;
		int height;
		int channels;

		texture(const GLchar* texPath, GLenum texType, GLenum internalFormat, GLenum format, bool flipVertical = false);
		static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
		void bind(int texUnit) const;
	private:
		unsigned char* data;
		GLenum textureType;
	};
}
