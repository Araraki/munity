#include "texture.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../tools/std_image.h"

namespace munity
{
	texture::texture(const GLchar* texPath, GLenum texType, GLenum internalFormat, GLenum format, bool flipVertical)
	{
		textureType = texType;

		glGenTextures(1, &ID);
		glBindTexture(textureType, ID);

		//float borderColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		//glTexParameterfv(textureType, GL_TEXTURE_BORDER_COLOR, borderColor);

		glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(flipVertical);

		data = stbi_load(texPath, &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(textureType, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(textureType);
		}
		else
		{
#ifdef _DEBUG
			std::cout << "Failed to load texture" << std::endl;
#endif
		}
		stbi_image_free(data);
	}

	unsigned texture::TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
#ifdef _DEBUG
			std::cout << "Texture failed to load at path: " << path << std::endl;
#endif
			stbi_image_free(data);
		}
		return textureID;
	}

	void texture::bind(int texUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + texUnit);
		glBindTexture(textureType, ID);
	}
}
