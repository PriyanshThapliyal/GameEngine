#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

void Engine::Window::Init(unsigned int width, unsigned int height, const char* title) 
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	m_Window = glfwCreateWindow(width, height, title , nullptr , nullptr);
	
	if (!m_Window)
	{
		std::cout << "Window Creation Failed" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent((GLFWwindow*)m_Window);

	glfwSetWindowSizeCallback((GLFWwindow*)m_Window, [](GLFWwindow* window, int width, int height)
		{
			std::cout << "Resized: " << width << " , " << height << std::endl;
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
	glfwDestroyWindow((GLFWwindow*)m_Window);
	glfwTerminate();
}

void Engine::Window::PollEvents()
{
	glfwPollEvents();
}

bool Engine::Window::ShouldClose() const
{
	return glfwWindowShouldClose((GLFWwindow*)m_Window);
}