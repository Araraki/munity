#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../base/singleton.h"
#include "camera.h"

namespace munity
{
	class input : public singleton<input>
	{
	public:
		static void initialize(GLFWwindow*, camera& );
		static void processing();
		//double CursorX() { return xpos; }
		//double CursorY() { return ypos; };
	private:
		static void cursor_pos_callback(GLFWwindow* , double , double );

		static GLFWwindow* window;
		static camera* editorCamera;
		static double xpos, ypos;
		static int MouseLeftState;
		static int MouseRightState;
		static int MouseTmpState;

		static bool firstMouse;
		static bool enableFPS;
		static float lastX, lastY;

		input() = default;
		~input() = default;
		input(const input&) {}
		input& operator= (const input&) { return *this; }
	};
}