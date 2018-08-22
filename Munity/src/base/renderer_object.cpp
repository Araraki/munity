#include "renderer_object.h"

namespace munity
{
	glm::vec3 renderer_object::default_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 renderer_object::default_rot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 renderer_object::default_scl = glm::vec3(1.0f, 1.0f, 1.0f);

	renderer_object::renderer_object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, bool visible)
								   : position(pos), rotation(rot), scale(sca), visible(visible){}

	renderer_object::~renderer_object() = default;

	glm::mat4 renderer_object::getRotationMat() const
		{ return glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z); }

	void renderer_object::renderer(){}

	void renderer_object::renderer(shader& shader){}
}
