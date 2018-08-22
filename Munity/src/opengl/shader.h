#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <glm/mat4x2.hpp>

namespace munity
{
	class shader
	{
	public:
		unsigned int ID;

		shader() = default;
		shader(const shader&);
		shader& operator=(shader&&);
		shader(const GLchar*, const GLchar*);		

		friend bool operator==(const shader& l, const shader& r) { return l.ID == r.ID; }
		friend bool operator!=(const shader& l, const shader& r) { return l.ID != r.ID;	}

		//~shader() { CancelShader(*this); }
		~shader() = default;
		void use();
		void setBool(const std::string &, const bool&) const;
		void setInt(const std::string &, const int&) const;
		void setFloat(const std::string &, const float&) const;
		void setVec3(const std::string&, const glm::vec3&) const;
		void setVec3(const std::string&, const float&, const float&, const float&) const;
		void setVec4(const std::string&, const glm::vec4&) const;
		void setVec4(const std::string&, const float&, const float&, const float&, const float&) const;
		void setMat4(const std::string&, const glm::mat4&) const;
		
		static std::vector<shader*> shaders;
		static void RegisteredShader(shader& shader);
		static void CancelShader(shader& shader);
	};
}
