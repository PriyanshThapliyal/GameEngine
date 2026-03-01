#pragma once
#include "Platform/Window/Window.h"

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
		void SwapBuffers();

	private:
		Window m_Window;

		static Application* s_Instance; // Static instance for global access

	protected:
		bool m_Running = true;
	};

	Application* CreateApplication();
}
