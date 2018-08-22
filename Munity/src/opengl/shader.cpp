#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/mat4x2.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace munity
{
	std::vector<shader*> shader::shaders = std::vector<shader*>();

	shader::shader(const shader& src)
	{
		this->ID = src.ID;
	}

	shader& shader::operator=(shader&& src)
	{
		this->ID = src.ID;
		return *this;
	}

	shader::shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		// Loading
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
#ifdef _DEBUG
			std::cout << "ERROR::Shader::File_not_succesfully_read" << std::endl;
#endif
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Compile
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
			std::cout << "ERROR::Shader::Vertex::Compilation_Failed\n" << infoLog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
			std::cout << "ERROR::Shader::Fragment::Compilation_Failed\n" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, nullptr, infoLog);
			std::cout << "ERROR::Shader::Program::Link_Failed\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
		RegisteredShader(*this);
	}

	void shader::use()
	{
		glUseProgram(ID);
	}

	void shader::setBool(const std::string& name, const bool& value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
	}

	void shader::setInt(const std::string& name, const int& value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}

	void shader::setFloat(const std::string& name, const float& value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	void shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
	}

	void shader::setVec3(const std::string& name, const float& x, const float& y, const float& z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void shader::setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
	}

	void shader::setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}

	void shader::setMat4(const std::string& name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		//glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void shader::RegisteredShader(shader& shader)
	{
		shaders.push_back(&shader);
	}

	void shader::CancelShader(shader& shader)
	{
		auto iter = std::find(shaders.begin(), shaders.end(), &shader);
		if (iter != shaders.end())
			shaders.erase(iter);
	}
}
