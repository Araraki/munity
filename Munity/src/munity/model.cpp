#include "model.h"

namespace munity
{
	model::model(const char* path, bool gamma)
				: renderer_object(default_pos, default_rot, default_scl, true),
	              gammaCorrection(gamma)
	{
		loadModel(path);
	}

	void model::renderer(shader& shader)
	{
		glm::mat4 model;
		model = glm::translate(model, position);
		model *= getRotationMat();
		model = glm::scale(model, scale);
		shader.use();
		shader.setMat4("model", model);
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].renderer(shader);
	}

	void model::loadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
#ifdef _DEBUG
			std::cout << "Error::Assimp::" << importer.GetErrorString() << std::endl;
#endif
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);
	}

	void model::processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* _mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(_mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}

	mesh model::processMesh(aiMesh* _mesh, const aiScene* scene)
	{
		std::vector<mesh::mVertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<mesh::mTexture> textures;

		for (unsigned int i = 0; i < _mesh->mNumVertices; ++i)
		{
			mesh::mVertex vertex;

			glm::vec3 vector;
			vector.x = _mesh->mVertices[i].x;
			vector.y = _mesh->mVertices[i].y;
			vector.z = _mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = _mesh->mNormals[i].x;
			vector.y = _mesh->mNormals[i].y;
			vector.z = _mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (_mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = _mesh->mTextureCoords[0][i].x;
				vec.y = _mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);

			vector.x = _mesh->mTangents[i].x;
			vector.y = _mesh->mTangents[i].y;
			vector.z = _mesh->mTangents[i].z;
			vertex.Tangent = vector;

			vector.x = _mesh->mBitangents[i].x;
			vector.y = _mesh->mBitangents[i].y;
			vector.z = _mesh->mBitangents[i].z;
			vertex.Bitangent = vector;

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < _mesh->mNumFaces; ++i)
		{
			aiFace face = _mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j)
				indices.push_back(face.mIndices[j]);
		}

		if (_mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[_mesh->mMaterialIndex];
			std::vector<mesh::mTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<mesh::mTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			std::vector<mesh::mTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			std::vector<mesh::mTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}

		return mesh(vertices, indices, textures);
	}

	std::vector<mesh::mTexture> model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<mesh::mTexture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data, str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				mesh::mTexture texture;
				texture.id = munity::texture::TextureFromFile(str.C_Str(), directory);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
			}
		}
		return textures;
	}
}
