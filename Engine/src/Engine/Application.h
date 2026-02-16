#pragma once
#include "Platform/Window/Window.h"

namespace Engine {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		Window m_Window;

	protected:
		bool m_Running = true;
	};

	Application* CreateApplication();
}
