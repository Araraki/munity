#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../base/object.h"
#include "../opengl/shader.h"
#include "../base/renderer_object.h"

namespace munity
{
	enum LightType
	{
		direction,
		point,
		spotlight
	};

	class light : public renderer_object
	{
	protected:
		static glm::vec3 nop;
		static float	 nopf;

		static glm::vec3 default_direction;
		static glm::vec3 default_ambient;
		static glm::vec3 default_diffuse;
		static glm::vec3 default_specular;

		static float	 default_constant;
		static float	 default_linear;
		static float	 default_quadratic;

		static float	 default_cosCutOff;
		static float	 default_cosOuterCutOff;

		static shader*	 outline_shader;

		light(LightType type, glm::vec3 pos);
	public:

		static std::vector<light*> lights;
		static void configlights();
		static void rendererlights();

		LightType type;
		renderer_object* lightCube = nullptr;
		shader* lightShader = nullptr;

		static void initialize();
		void renderer(shader& shader) override;
		virtual void config(shader& shader, int count = 0) {}
		~light() = default;
	};
}
