#include <enpch.h>
#include "Application.h"
#include "Platform/Window/Window.h"
#include "Time.h"
#include "Engine/Log.h"

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

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		EN_CORE_ERROR("Window close event received, shutting down application.");
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		EN_CORE_INFO("Window resized to {0}x{1}", e.GetWidth(), e.GetHeight());
		return false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
	
		//dispatcher.Dispatch<WindowCloseEvent>(
		//	std::bind(&Application::OnWindowClose, this, std::placeholders::_1)
		//);     This is now considered anold fashioned in modern C++ instead we use this now
		// Lambda expression
		dispatcher.Dispatch<WindowCloseEvent>(
			[this](WindowCloseEvent& event) {
				return OnWindowClose(event);
			});

		dispatcher.Dispatch<WindowResizeEvent>(
			[this](WindowResizeEvent& event) {
				return OnWindowResize(event);
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