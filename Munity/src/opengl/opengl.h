#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../base/singleton.h"
#include "../munity/global.h"

class opengl : munity::singleton<opengl>
{
public:
	static GLFWwindow* initialize();
	static bool Running();
	static void Clear();
private:
	static void framebuffer_size_callback(GLFWwindow* win, int w, int h)
	{
		glViewport(0, 0, w, h);
		munity::global::updatewh(w, h);
	}

	GLFWwindow* window = nullptr;

	opengl() = default;
	~opengl() = default;
	opengl(const opengl&) {}
	opengl& operator=(const opengl&) { return *this; }
};
