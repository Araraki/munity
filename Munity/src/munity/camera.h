#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../munity/global.h"
#include "../base/object.h"

namespace munity
{
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class camera : public object
	{
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 world_up;

		float yaw = 0.0f;
		float pitch = 0.0f;

		float move_speed;
		float mouse_sensitivity;
		float zoom;
		
		float nearplane;
		float farplane;

		camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		       float yaw = YAW, float pitch = PITCH,
			   float nearplane = 0.1f, float farplane = 100.0f);
		void updateview() const;
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);
	private:
		void updateCameraVectors();

		static float YAW;
		static float PITCH;
		static float SPEED;
		static float SENSITIVITY;
		static float ZOOM;
	};
}
