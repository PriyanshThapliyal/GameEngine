#include <enpch.h>
#include "Window.h"
#include <GLFW/glfw3.h>
#include "Engine/Log.h"
#include "Engine/Events/ApplicationEvent.h"

static bool s_GLFWInititalized = false;

void Engine::Window::Init(unsigned int width, unsigned int height, const char* title) 
{	
	if (!s_GLFWInititalized) 
	{
		if (!glfwInit())
		{
			EN_CORE_ERROR("Failed to initialize GLFW");
			return;
		}
		s_GLFWInititalized = true;
	}
	

	GLFWwindow* window = glfwCreateWindow(width, height, title , nullptr , nullptr);
	
	if (!window)
	{
		EN_CORE_ERROR("Failed to create GLFW window");
		glfwTerminate();
		return;
	}

	m_Window = window;

	glfwMakeContextCurrent((GLFWwindow*)m_Window);

	glfwSetWindowUserPointer((GLFWwindow*)m_Window, &m_Data); // Set the user pointer to our WindowData struct for later use in callbacks

	glfwSetWindowCloseCallback((GLFWwindow*)m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // Retrieve the WindowData from the user pointer
			
			WindowCloseEvent event; // Create a WindowCloseEvent
			data.m_EventCallback(event);
		});

	m_Data.m_Width = width;
	m_Data.m_Height = height;

	glfwSetWindowSizeCallback((GLFWwindow*)m_Window,
		[](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.m_Width = width;
			data.m_Height = height;

			WindowResizeEvent event(width, height);
			data.m_EventCallback(event);
		});
	}
    
Engine::Window::Window(unsigned int width , unsigned int height , const char* title)
{
	Init(width, height, title);
}

Engine::Window::~Window()
{
	Shutdown();
}

void Engine::Window::Shutdown()
{
	if (m_Window) {
		glfwDestroyWindow((GLFWwindow*)m_Window);
		m_Window = nullptr;
	}

	if(s_GLFWInititalized)
	{
		s_GLFWInititalized = false;
	}
}

void Engine::Window::PollEvents()
{
	glfwPollEvents();
}

void Engine::Window::SwapBuffers(void* m_Window)
{
	glfwSwapBuffers((GLFWwindow*)m_Window);
}

unsigned int Engine::Window::GetWidth() const
{
	return m_Data.m_Width;
}
unsigned int Engine::Window::GetHeight() const
{
	return m_Data.m_Height;
}

void Engine::Window::SetEventCallback(const EventCallbackFn& callback)
{
	m_Data.m_EventCallback = callback;
}