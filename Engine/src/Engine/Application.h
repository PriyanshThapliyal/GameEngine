#pragma once
#include "Platform/Window/Window.h"

namespace Engine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	protected:
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();

	private: 
		void PollEvents();

	private:
		Window m_Window;

	protected:
		bool m_Running = true;
	};

	Application* CreateApplication();
}
