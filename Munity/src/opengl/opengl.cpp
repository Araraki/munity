#include "opengl.h"

#include "../munity/global.h"
#include <iostream>

GLFWwindow* opengl::initialize()
{
	_inst = new opengl();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	_inst->window = glfwCreateWindow(munity::global::appWidth, munity::global::appHeight, munity::global::appName, nullptr, nullptr);
	if (_inst->window == nullptr)
	{
#ifdef _DEBUG
		std::cout << "Failed to create GLFW window" << std::endl;
#endif
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(_inst->window);
	glfwSetFramebufferSizeCallback(_inst->window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
#ifdef _DEBUG
		std::cout << "Failed to initialize GLAD" << std::endl;
#endif
		return nullptr;
	}

	return _inst->window;
}

bool opengl::Running()
{
	return !glfwWindowShouldClose(_inst->window);
}

void opengl::Clear()
{
	glfwTerminate();
}
