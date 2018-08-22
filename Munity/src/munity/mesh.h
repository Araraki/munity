#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/types.h>

#include "../base/renderer_object.h"

namespace munity
{
	class mesh : public renderer_object
	{
	public:
		struct mVertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};
		struct mTexture
		{
			unsigned int id;
			std::string type;
			aiString path;
		};

		//unsigned int vao = 0, vbo = 0, ebo = 0;
		unsigned int ebo = 0;
		std::vector<mVertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<mTexture> textures;

		mesh(std::vector<mVertex> vertices, std::vector<unsigned int> indices, std::vector<mTexture> textures);
		void renderer(shader& shader) override;
		~mesh() = default;
	};
}
