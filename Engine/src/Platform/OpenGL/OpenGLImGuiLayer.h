#pragma once

#include "../../Engine/Core/LayerStack/ImGui/ImGuiLayer.h"

struct GLFWwindow;

namespace Engine
{
	class OpenGLImGuiLayer : public ImGuiLayer
	{
	public:
		OpenGLImGuiLayer();

		virtual ~OpenGLImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void Begin() override;
		virtual void End() override;

	private:
		GLFWwindow* m_Window = nullptr;
	};
}