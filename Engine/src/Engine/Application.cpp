#include <enpch.h>
#include "Application.h"
#include "Platform/Window/Window.h"
#include "Time.h"
#include "Engine/Log.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {
	Application::Application() : m_Window(1280, 720, "Engine")
	{
		s_Instance = this;
		m_Window.SetEventCallback([this](Event& e) 
			{ OnEvent(e); });
	}

	Application::~Application()
	{
	}

	Application* Application::s_Instance = nullptr;

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
	
		dispatcher.Dispatch<WindowCloseEvent>(
			[this](WindowCloseEvent& e) 
			{ 
				m_Running = false; 
				return true; 
			});
	}
	void Application::PollEvents()
	{
		m_Window.PollEvents();
	}

	void Application::SwapBuffers()
	{
		m_Window.SwapBuffers(m_Window.GetNativeWindow());
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
			
			PollEvents();	// Poll and handle events
			OnUpdate(deltaTime);		// Game Logic
			OnRender();		// Placeholder Render
			SwapBuffers();	// Swap the front and back buffers
		}
	}
}