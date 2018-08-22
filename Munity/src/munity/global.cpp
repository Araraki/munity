#include "global.h"
#include <GLFW/glfw3.h>

namespace munity
{
	const char* global::appName = "";
	int global::appWidth = 0;
	int global::appHeight = 0;
	float global::appAspect;
	
	float time::deltaTime = 0.0f;
	float time::lastFrame = 0.0f;
	float time::current = 0.0f;

	void global::initialize(const char* name, int width, int height)
	{
		global(name, width, height);
	}

	global::global(const char* name, int width, int height)
	{
		appName = name;
		appWidth = width;
		appHeight = height;
		appAspect = float(appWidth) / float(appHeight);
	}

	void global::updatewh(int w, int h)
	{
		appWidth = w;
		appHeight = h;
		appAspect = float(appWidth) / float(appHeight);
	}

	void time::calcDelta()
	{
		current = float(glfwGetTime());
		deltaTime = current - lastFrame;
		lastFrame = current;
	}
}
