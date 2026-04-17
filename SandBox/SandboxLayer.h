#pragma once

#include <memory>
#include "Engine.h"
#include "Engine/Core/Layer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"

#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/SpriteRendererComponent.h"



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

		auto entity = m_Scene.CreateEntity();

		auto& transform = entity.AddComponent<Engine::TransformComponent>();
		auto& sprite = entity.AddComponent<Engine::SpriteRendererComponent>();

		transform.Position = { 0.0f, 0.0f, 0.0f };
		transform.Scale = { 0.5, 0.5f, 1.0f};
		sprite.Color = { 1.0f, 1.0f, 0.0f, 1.0f };	

		Engine::Renderer2D::Init();
		Engine::RenderCommand::SetClearColor(0.1f,0.1f,0.1f,1.0f);
	}

	void OnUpdate(float deltaTime) override
	{
		m_Angle += deltaTime;
		
		m_CameraController.OnUpdate(deltaTime);

	}

	void OnRender() override
	{
		Engine::RenderCommand::Clear();

		m_Scene.OnRender(m_CameraController.GetCamera());
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
	Engine::Scene m_Scene;
};
