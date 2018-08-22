#pragma once
#include "../base/singleton.h"

namespace munity
{
	class global
	{
	public:
		static const char* appName;
		static int appWidth;
		static int appHeight;
		static float appAspect;		

		static void initialize(const char* name, int width, int height);
		static void updatewh(int w, int h);
	private:
		global() = default;
		global(const char* name, int width, int height);
		~global() = default;
	};

	class time : public singleton<time>
	{
	public:
		static float current;
		static float deltaTime;
		static void calcDelta();
	private:
		static float lastFrame;
	};
}
	