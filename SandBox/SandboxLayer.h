#pragma once

#include <memory>

#include "Engine/Core/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Core/Log.h"
#include "Engine/Events/ApplicationEvent.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Renderer/CameraController.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Texture.h"

#include <memory>


class SandboxLayer : public Engine::Layer
{
public:
	SandboxLayer()
		: Layer("SandboxLayer")
		, m_CameraController(1280.f / 720.0f)
	{}

	void OnAttach() override
	{
		EN_CORE_WARN("SandboxLayer Attached");
		Engine::Renderer2D::Init();

		Engine::RenderCommand::SetClearColor(0.0f, 1.0f, 0.0f, 1.0f);

		m_Texture = std::make_unique<Engine::Texture>("Engine/assets/Textures/test.png");
	}

	void OnUpdate(float deltaTime) override
	{
		m_Angle += deltaTime;
		
		m_CameraController.OnUpdate(deltaTime);

	}

	void OnRender() override
	{
		Engine::RenderCommand::Clear();

		auto& camera = m_CameraController.GetCamera();

		Engine::Renderer2D::SetCamera(camera);

		// Start Batch
		Engine::Renderer2D::BeginScene();
		
		Engine::Renderer2D::DrawQuad({  0.5f,  0.5f }, { 0.5f, 0.5f }, *m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
		Engine::Renderer2D::DrawQuad({ -0.5f,  0.5f }, { 0.5f, 0.5f }, *m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
		Engine::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.5f, 0.5f }, *m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
		Engine::Renderer2D::DrawQuad({  0.5f, -0.5f }, { 0.5f, 0.5f }, *m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});
		
		// End Batch (this calls flush)
		Engine::Renderer2D::FlushAndReset();
	}

	void OnEvent(Engine::Event& e) override
	{
		if (e.GetEventType() == Engine::EventType::KeyPressed)
		{
			auto& keyEvent = static_cast<Engine::KeyPressedEvent&>(e);

			EN_CORE_TRACE("Key Pressed : {0} , Repeat : {1}", (int)keyEvent.GetKeyCode(), keyEvent.IsRepeat());
		}

		//if (e.GetEventType() == Engine::EventType::MouseMoved)
		//{
		//	auto& mouseEvent = static_cast<Engine::MouseMovedEvent&>(e);

		//	EN_CORE_TRACE("Mouse Moved : {0} , {1}", mouseEvent.GetX(), mouseEvent.GetY());
		//}

		if (e.GetEventType() == Engine::EventType::MouseButtonPressed)
		{
			auto& mouseEvent = static_cast<Engine::MouseButtonPressedEvent&>(e);

			EN_CORE_TRACE("Mouse Button Pressed : {0}", mouseEvent.GetMouseButton());
		}

		if (e.GetEventType() == Engine::EventType::MouseScrolled)
		{
			auto& mouseEvent = static_cast<Engine::MouseScrolledEvent&>(e);

			EN_CORE_TRACE("Mouse Scrolled : {0} , {1}", mouseEvent.GetXOffset(), mouseEvent.GetYOffset());
		}

		if (e.GetEventType() == Engine::EventType::WindowResize)
		{
			auto& resizeEvent = static_cast<Engine::WindowResizeEvent&>(e);

			uint32_t width = resizeEvent.GetWidth();
			uint32_t height = resizeEvent.GetHeight();

			// Fix ViewPort
			Engine::RenderCommand::SetViewport(0, 0, width, height);

			// Update Camera
			m_CameraController.OnResize(
				(float)width,
				(float)height
			);

		}
	}

	void OnDetach()
	{}

private:
	float m_Angle = 0.0f;
	std::unique_ptr<Engine::Texture> m_Texture;
	Engine::CameraController m_CameraController;
};
