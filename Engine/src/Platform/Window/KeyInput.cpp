#include <enpch.h>
#include "Engine/Input.h"
#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}
}