#pragma once
#include "Platform/Window/Window.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/Event.h"

namespace Engine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		Window& GetWindow() { return m_Window; }

		static Application& Get() { return *s_Instance; }

	protected:
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();

	private: 
		void PollEvents();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void SwapBuffers();

	private:
		Window m_Window;

		static Application* s_Instance; // Static instance for global access

	protected:
		bool m_Running = true;
	};

	Application* CreateApplication();
}
