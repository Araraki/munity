#include "camera.h"

#include "../opengl/shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace munity
{
	float camera::YAW = -90.0f;
	float camera::PITCH = 0.0f;
	float camera::SPEED = 2.5f;
	float camera::SENSITIVITY = 0.1f;
	float camera::ZOOM = 45.0f;

	camera::camera(glm::vec3 position, glm::vec3 up, float yaw,
				   float pitch, float nearplane, float farplane)
				 : front(glm::vec3(0.0f, 0.0f, -1.0f)),
				   move_speed(SPEED),
				   mouse_sensitivity(SENSITIVITY),
				   zoom(ZOOM)
	{
		this->position = position;
		this->world_up = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->nearplane = nearplane;
		this->farplane = farplane;
		updateCameraVectors();
	}

	void camera::updateview() const
	{
		glm::mat4 projection = glm::perspective(glm::radians(zoom), global::appAspect, nearplane, farplane);
		glm::mat4 ortho = glm::ortho(0.0f, float(global::appWidth), 0.0f, float(global::appHeight));
		glm::mat4 lookat = glm::lookAt(position, position + front, up);
		for (shader* shader : shader::shaders)
		{
			shader->use();
			shader->setMat4("projection", projection);
			shader->setMat4("ortho", ortho);
			shader->setMat4("view", lookat);
		}
	}

	void camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = move_speed * deltaTime;
		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= right * velocity;
		if (direction == RIGHT)
			position += right * velocity;
		if (direction == UP)
			position -= world_up * velocity;
		if (direction == DOWN)
			position += world_up * velocity;
	}

	void camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= mouse_sensitivity;
		yoffset *= mouse_sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}
		updateCameraVectors();
	}

	void camera::ProcessMouseScroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

	void camera::updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw))* cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw))*cos(glm::radians(this->pitch));

		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, world_up));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
}
