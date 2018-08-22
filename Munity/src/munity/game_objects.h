#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../base/renderer_object.h"
#include "light.h"
#include "ui.h"
#include "texture.h"

namespace munity
{
	// ----------------------- lights ----------------------------------
	class direction_light : public light
	{
	public:
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		direction_light(glm::vec3 direction = default_direction,
			glm::vec3 ambient = default_ambient,
			glm::vec3 diffuse = default_diffuse,
			glm::vec3 specular = default_specular);
		void config(shader& shader, int count) override final;
	};

	class point_light : public light
	{
	public:
		glm::vec3	ambient;
		glm::vec3	diffuse;
		glm::vec3	specular;
		float		constant;
		float		linear;
		float		quadratic;

		point_light(glm::vec3	position = default_pos,
			glm::vec3	ambient = default_ambient,
			glm::vec3	diffuse = default_diffuse,
			glm::vec3	specular = default_specular,
			float		constant = default_constant,
			float		linear = default_linear,
			float		quadratic = default_quadratic);
		void config(shader& shader, int count) override final;
	};

	class spotlight : public light
	{
	public:
		glm::vec3	direction;
		glm::vec3	ambient;
		glm::vec3	diffuse;
		glm::vec3	specular;
		float		constant;
		float		linear;
		float		quadratic;
		float		cosCutOff;
		float		cosOuterCutOff;

		spotlight(glm::vec3	position = default_pos,
			glm::vec3	direction = default_direction,
			glm::vec3	ambient = default_ambient,
			glm::vec3	diffuse = default_diffuse,
			glm::vec3	specular = default_specular,
			float		constant = default_constant,
			float		linear = default_linear,
			float		quadratic = default_quadratic,
			float		coscutoff = default_cosCutOff,
			float		cosoutercutoff = default_cosOuterCutOff);
		void config(shader& shader, int count) override final;
	};


	// ----------------------- shapes ----------------------------------
	class light_cube : public renderer_object
	{
	public:
		light_cube(glm::vec3 pos = glm::vec3(0.0f),
				  glm::vec3 rot = glm::vec3(0.0f),
				  glm::vec3 sca = glm::vec3(0.2f));
		virtual ~light_cube();
		void renderer(shader& shader) override;
	};

	class uv_cube : public renderer_object
	{
	public:
		uv_cube(glm::vec3 pos = glm::vec3(0.0f),
			   glm::vec3 rot = glm::vec3(0.0f),
			   glm::vec3 sca = glm::vec3(1.0f));
		virtual ~uv_cube();
		void renderer(shader& shader) override;
	};

	class quad : public renderer_object
	{
		public:
		quad(glm::vec3 pos = glm::vec3(0.0f),
			 glm::vec3 rot = glm::vec3(0.0f),
			 glm::vec3 sca = glm::vec3(1.0f));
		virtual ~quad();
		void renderer(shader& shader) override;
	};



	// ----------------------- uis ----------------------------------
	class button : public ui
	{
	protected:
		glm::vec4 lineColor;
		glm::vec4 fillColor;

		texture btnTex;
		shader btnShader;
		text  textContent;
	public:
		button(unsigned int posx, unsigned int posy,
		       unsigned int w, unsigned int h, std::string content);
		virtual ~button();
		void renderer() override;
		void renderer(shader& shader) override;
	};
}
