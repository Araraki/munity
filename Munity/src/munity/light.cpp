#include "light.h"
#include "game_objects.h"

namespace munity
{
	std::vector<light*> light::lights	= std::vector<light*>();

	glm::vec3 light::nop				= glm::vec3( 0.0f,	 0.0f,	 0.0f);
	float	  light::nopf				= 0.0f;
	
	glm::vec3 light::default_direction	= glm::vec3( 0.0f,  -1.0f,   0.0f);
	glm::vec3 light::default_ambient	= glm::vec3( 0.05f,  0.05f,  0.05f);
	glm::vec3 light::default_diffuse	= glm::vec3( 0.8f,   0.8f,   0.8f);
	glm::vec3 light::default_specular	= glm::vec3( 1.0f,   1.0f,   1.0f);
	
	float	  light::default_constant	= 1.0f;
	float	  light::default_linear		= 0.09f;
	float	  light::default_quadratic	= 0.032f;
	
	float	  light::default_cosCutOff		= glm::cos(glm::radians(12.5f));
	float	  light::default_cosOuterCutOff = glm::cos(glm::radians(15.0f));

	shader*	  light::outline_shader			= nullptr;

	light::light(LightType type, glm::vec3 pos)
		: renderer_object(pos)
	{
		this->type = type;
		this->lightShader = new shader("Res/Shaders/lamp.vert", "Res/Shaders/lamp.frag");
		this->visible = true;
		this->lightCube = new light_cube(pos, default_rot, glm::vec3(0.2f));
	}

	void light::configlights()
	{
		int pointLightCount = 0;
		for (light* light : lights)
		{
			for (shader* shader : shader::shaders)
				light->config(*shader, pointLightCount);
			if (light->type == LightType::point)
				pointLightCount++;
		}
	}

	void light::rendererlights()
	{
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0xff);

		for (light* light : lights)
		{
			if (light->visible)
				light->renderer(*light->lightShader);
		}

		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		for (light* light : lights)
		{
			light->lightCube->scale *= 1.25f;
			if (light->visible)
				light->renderer(*outline_shader);
			light->lightCube->scale *= 0.8f;
		}

		glStencilMask(0xff);
		glEnable(GL_DEPTH_TEST);
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilMask(0x00);
	}

	void light::initialize()
	{
		outline_shader = new shader("res/shaders/outline.vert", "res/shaders/outline.frag");
	}

	void light::renderer(shader& shader)
	{
		lightCube->position = position;
		lightCube->renderer(shader);
	}
}
