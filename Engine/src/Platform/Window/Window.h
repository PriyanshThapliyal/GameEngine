#pragma once

namespace Engine {
	
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		void PollEvents();
		bool ShouldClose() const;

	private:
		void Init(unsigned int width, unsigned int height, const char* title);
		void Shutdown();


	private:
		void* m_Window; // Hides GLFWwindow* to avoid including GLFW in the header
	};

}

// Note : The implementation of the Window class is in the corresponding .cpp file, and it uses GLFW for window management. The header file only declares the interface of the Window class, while the implementation details are hidden in the .cpp file to avoid exposing GLFW-specific code in the header.
