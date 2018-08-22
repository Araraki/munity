#pragma once
#include <vector>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.h"
#include "texture.h"
#include "../base/renderer_object.h"
#include "../opengl/shader.h"


namespace munity
{
	class model : public renderer_object
	{
	public:
		std::vector<mesh::mTexture> textures_loaded;
		std::vector<mesh> meshes;
		std::string directory;
		bool gammaCorrection;

		model(const char* path, bool gamma = false);
		~model(){}
		void renderer(shader& shader) override;
	private:
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<mesh::mTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
