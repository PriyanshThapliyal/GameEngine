#include "Application.h"
#include "Platform/Window/Window.h"

namespace Engine {
	Application::Application() : m_Window(1280, 720, "Engine")
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window.PollEvents();

			if(m_Window.ShouldClose())
				m_Running = false;
		}
	}
}