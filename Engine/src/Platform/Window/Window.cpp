#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

static bool s_GLLFWInititalized = false;

void Engine::Window::Init(unsigned int width, unsigned int height, const char* title) 
{	
	if (!s_GLLFWInititalized) 
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return;
		}
		s_GLLFWInititalized = true;
	}
	

	GLFWwindow* window = glfwCreateWindow(width, height, title , nullptr , nullptr);
	
	if (!window)
	{
		std::cout << "Window Creation Failed" << std::endl;
		glfwTerminate();
		return;
	}

	m_Window = window;

	glfwMakeContextCurrent((GLFWwindow*)m_Window);

	glfwSetWindowSizeCallback((GLFWwindow*)m_Window, 
		[](GLFWwindow* window, int width, int height)
		{
			#ifdef EN_DEBUG
				std::cout << "Window Size Changed: " << width << " , " << height << std::endl;
			#endif
			glViewport(0, 0, width, height);
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

	if(s_GLLFWInititalized)
	{
		glfwTerminate();
		s_GLLFWInititalized = false;
	}
}

void Engine::Window::PollEvents()
{
	glfwPollEvents();
}

bool Engine::Window::ShouldClose() const
{
	if (!m_Window) return true;

	return glfwWindowShouldClose((GLFWwindow*)m_Window);
}