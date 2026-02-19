#include "Application.h"
#include "Platform/Window/Window.h"
#include "GLFW/glfw3.h"

namespace Engine {
	Application::Application() : m_Window(1280, 720, "Engine")
	{
	}

	Application::~Application()
	{
	}

	void Application::PollEvents() {
		m_Window.PollEvents();

		if (m_Window.ShouldClose())
			m_Running = false;
	}

	void Application::OnUpdate(float deltaTime) {}

	void Application::OnRender() {}

	void Application::Run()
	{
		
		float lastTime = glfwGetTime();
		while (m_Running)
		{
			float currentTime = glfwGetTime();
			float deltaTime = currentTime - lastTime;
			PollEvents();   // Input / OS messages
			OnUpdate(deltaTime);		// Game Logic
			OnRender();		// Placeholder Render
			lastTime = currentTime;
		}
	}
}