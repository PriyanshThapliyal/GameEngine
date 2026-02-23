#include "Application.h"
#include "Platform/Window/Window.h"
#include "Time.h"

namespace Engine {
	Application::Application() : m_Window(1280, 720, "Engine")
	{
		s_Instance = this;
	}

	Application::~Application()
	{
	}

	Application* Application::s_Instance = nullptr;

	void Application::PollEvents() {
		m_Window.PollEvents();

		if (m_Window.ShouldClose())
			m_Running = false;
	}

	void Application::OnUpdate(float deltaTime) {}

	void Application::OnRender() {}

	void Application::Run()
	{

		float lastTime = Time::GetTime();
		while (m_Running)
		{
			float currentTime = Time::GetTime();
			float deltaTime = currentTime - lastTime;
			PollEvents();   // Input / OS messages
			OnUpdate(deltaTime);		// Game Logic
			OnRender();		// Placeholder Render
			lastTime = currentTime;
		}
	}
}