#pragma once
#include "Platform/OpenGL/Window/Window.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/Event.h"
#include "Engine/Core/LayerStack/LayerStack.h"

namespace Engine {
	class OpenGLImGuiLayer;

	class Application
	{
	public:
		Application(const char* title = "Engine");
		virtual ~Application();

		void Run();
		Window& GetWindow() { return m_Window; }

		static Application& Get() { return *s_Instance; }
		virtual void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	protected:
		virtual void OnUpdate(float deltaTime);
		virtual void OnRender();

	private: 
		void PollEvents();
		
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void SwapBuffers();

	private:
		Window m_Window;
		LayerStack m_LayerStack;
		OpenGLImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance; // Static instance for global access

	protected:
		bool m_Running = true;
	};

	Application* CreateApplication();
}
