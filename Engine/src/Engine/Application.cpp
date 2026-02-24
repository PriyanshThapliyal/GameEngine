#include "Application.h"
#include "Platform/Window/Window.h"
#include "Time.h"
#include "Engine/Log.h"

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
		if (m_Window.WasResized()) 
			EN_CORE_INFO("Window resized: {0}x{1}", m_Window.GetWidth(), m_Window.GetHeight());
			
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
			lastTime = currentTime;
			PollEvents();   // Input / OS messages
			OnUpdate(deltaTime);		// Game Logic
			OnRender();		// Placeholder Render
		}
	}
}