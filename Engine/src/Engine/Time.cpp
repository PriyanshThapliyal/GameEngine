#include "Time.h"
#include "GLFW/glfw3.h"

namespace Engine
{
	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}
}