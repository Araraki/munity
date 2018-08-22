#include "input.h"
#include "global.h"
#include <iostream>

namespace munity
{

	GLFWwindow* input::window = nullptr;
	camera* input::editorCamera = nullptr;
	double input::xpos, input::ypos;
	int input::MouseLeftState = GLFW_RELEASE;
	int input::MouseRightState = GLFW_RELEASE;
	int input::MouseTmpState;

	void input::initialize(GLFWwindow* win, camera& cam)
	{
		_inst = new input();
		window = win;
		editorCamera = &cam;
		glfwSetCursorPosCallback(window, cursor_pos_callback);
	}

	void input::processing()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
			return;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::FORWARD, time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::BACKWARD, time::deltaTime);

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::LEFT, time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::RIGHT, time::deltaTime);

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::UP, time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			editorCamera->ProcessKeyboard(Camera_Movement::DOWN, time::deltaTime);


		MouseTmpState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (MouseTmpState != MouseLeftState)
		{
			MouseLeftState = MouseTmpState;
			if (MouseLeftState == GLFW_PRESS)
			{
				glfwGetCursorPos(window, &xpos, &ypos);
#ifdef _DEBUG
				std::cout << "Left Press x:" << xpos << "\ty:" << ypos << "\n";
#endif
			}
			if (MouseLeftState == GLFW_RELEASE)
			{
				glfwGetCursorPos(window, &xpos, &ypos);
#ifdef _DEBUG
				std::cout << "Left Release x:" << xpos << "\ty:" << ypos << "\n";
#endif
			}
		}

		MouseTmpState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		if (MouseTmpState != MouseRightState)
		{
			MouseRightState = MouseTmpState;
			if (MouseRightState == GLFW_PRESS)
			{
				glfwGetCursorPos(window, &xpos, &ypos);
#ifdef _DEBUG
				std::cout << "Right Press x:" << xpos << "\ty:" << ypos << "\n";
#endif
				enableFPS = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			if (MouseRightState == GLFW_RELEASE)
			{
				glfwGetCursorPos(window, &xpos, &ypos);
#ifdef _DEBUG
				std::cout << "Right Release x:" << xpos << "\ty:" << ypos << "\n";
#endif
				enableFPS = false;
				firstMouse = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
	}

	bool input::firstMouse = true;
	bool input::enableFPS = false;
	float input::lastX = -1;
	float input::lastY = -1;
	void input::cursor_pos_callback(GLFWwindow* window, double x, double y)
	{
		if (enableFPS)
		{
			_inst->xpos = float(x);
			_inst->ypos = float(y);
#ifdef _DEBUG
			std::cout << "x:" << x << "\ty:" << y << "\n";
#endif
			if (firstMouse)
			{
				lastX = float(_inst->xpos);
				lastY = float(_inst->ypos);
				firstMouse = false;
			}

			float xoffset = float(_inst->xpos) - lastX;
			float yoffset = lastY - float(_inst->ypos);

			_inst->editorCamera->ProcessMouseMovement(xoffset, yoffset);

			lastX = float(_inst->xpos);
			lastY = float(_inst->ypos);
		}
	}
}
