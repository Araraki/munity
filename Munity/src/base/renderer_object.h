#pragma once
#include "object.h"

#include "../opengl/shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace munity
{
	class renderer_object : public object
	{
	protected:
		static glm::vec3 default_pos;
		static glm::vec3 default_rot;
		static glm::vec3 default_scl;

		renderer_object(glm::vec3 pos = default_pos,
						glm::vec3 rot = default_rot,
						glm::vec3 sca = default_scl,
		                bool visible = true);
		virtual ~renderer_object();
		glm::mat4 getRotationMat() const;
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		bool	  visible;
		
		unsigned int vao = 0;
		unsigned int vbo = 0;
		unsigned int vertexCount;

		virtual void renderer();
		virtual void renderer(shader& shader);
	};
}
