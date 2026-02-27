#include <enpch.h>
#include "WindowsInput.h"
#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	Input* Input::s_Instance = new WindowsInput(); // Initialize the static instance of Input

	namespace
	{
		static int KeyCodeToGLFW(KeyCode key)
		{
			switch (key)
			{
			case KeyCode::W: return GLFW_KEY_W;
			case KeyCode::A: return GLFW_KEY_A;
			case KeyCode::S: return GLFW_KEY_S;
			case KeyCode::D: return GLFW_KEY_D;
			default:
				return -1;
			}
		}

		static int MouseCodeToGLFW(MouseCode button)
		{
			switch (button)
			{
			case MouseCode::Left: return GLFW_MOUSE_BUTTON_LEFT;
			case MouseCode::Right: return GLFW_MOUSE_BUTTON_RIGHT;
			case MouseCode::Middle: return GLFW_MOUSE_BUTTON_MIDDLE;
			default:
				return -1;
			}
		}
	}
	

	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		int glfwKey = KeyCodeToGLFW(key);
		
		if(glfwKey == -1)
			return false; // Invalid key code

		auto state = glfwGetKey(window, glfwKey);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());
		
		int glfwButton = MouseCodeToGLFW(button);
		if (glfwButton == -1)
			return false; // Invalid mouse button code

		auto state = glfwGetMouseButton(window, glfwButton);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}	
}