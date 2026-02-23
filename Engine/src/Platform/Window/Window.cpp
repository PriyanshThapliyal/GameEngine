#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

static bool s_GLFWInititalized = false;

void Engine::Window::Init(unsigned int width, unsigned int height, const char* title) 
{	
	if (!s_GLFWInititalized) 
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			return;
		}
		s_GLFWInititalized = true;
	}
	

	GLFWwindow* window = glfwCreateWindow(width, height, title , nullptr , nullptr);
	
	if (!window)
	{
		std::cout << "Window Creation Failed" << std::endl;
		glfwTerminate();
		return;
	}

	m_Window = window;
	glfwSetWindowUserPointer((GLFWwindow*)m_Window, this); // Set the user pointer to the Window instance

	glfwMakeContextCurrent((GLFWwindow*)m_Window);
	m_Width = width;
	m_Height = height;

	glfwSetWindowSizeCallback((GLFWwindow*)m_Window, 
		[](GLFWwindow* window, int width, int height)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_Width = width;
			win->m_Height = height;

			#ifdef EN_DEBUG
				std::cout << "Window Size Changed: " << width << " , " << height << std::endl;
			#endif
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
		glfwTerminate();
		s_GLFWInititalized = false;
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