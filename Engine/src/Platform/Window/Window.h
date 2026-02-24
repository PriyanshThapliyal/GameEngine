#pragma once

namespace Engine {
	
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const char* title);
		~Window();

		void PollEvents();
		bool ShouldClose() const;
		bool WasResized() ;
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		void* GetNativeWindow() const { return m_Window; } // Provides access to the native window for internal use

	private:
		void Init(unsigned int width, unsigned int height, const char* title);
		void Shutdown();


	private:
		void* m_Window = nullptr; // Hides GLFWwindow* to avoid including GLFW in the header
		
		struct m_Data{
			bool CloseRequested = false;
			bool Resized = false;
			unsigned int m_Width = 0;
			unsigned int m_Height = 0;
		};
		m_Data m_Data;
	};

}

// Note : The implementation of the Window class is in the corresponding .cpp file, and it uses GLFW for window management. The header file only declares the interface of the Window class, while the implementation details are hidden in the .cpp file to avoid exposing GLFW-specific code in the header.
