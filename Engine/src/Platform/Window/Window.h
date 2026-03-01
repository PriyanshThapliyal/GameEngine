#pragma once
#include <functional>

namespace Engine {

	class Event; // Forward  declaration

	using EventCallbackFn = std::function<void(Event&)>;
	// Define a type for event callback functions that take an Event reference as a parameter


	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		Window(const Window&) = delete; // Delete copy constructor to prevent copying of the Window class
		Window& operator = (const Window&) = delete; // Delete copy assignment operator to prevent copying of the Window class
		void PollEvents();
		void SwapBuffers(void* m_Window);

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		void* GetNativeWindow() const { return m_Window; } // Provides access to the native window for internal use
		void SetEventCallback(const EventCallbackFn& callback);


	private:
		void Init(unsigned int width, unsigned int height, const char* title);
		void Shutdown();


	private:
		void* m_Window = nullptr; // Hides GLFWwindow* to avoid including GLFW in the header

		struct WindowData {
			unsigned int m_Width = 0;
			unsigned int m_Height = 0;

			EventCallbackFn m_EventCallback; // Function pointer for event callback
		};

		WindowData m_Data;
	};
}


// Note : The implementation of the Window class is in the corresponding .cpp file, and it uses GLFW for window management. The header file only declares the interface of the Window class, while the implementation details are hidden in the .cpp file to avoid exposing GLFW-specific code in the header.
