#pragma once

#include <memory>

#include "Engine/Core/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Core/Log.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Renderer/CameraController.h"

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
		m_Shader = std::make_unique<Engine::Shader>(
			"Engine/assets/Shaders/triangle.vert",
			"Engine/assets/Shaders/triangle.frag"
		);
		EN_CORE_WARN("Shader Compiled");

		float vertices[] = {
			0.0f,  0.5f, 0.0f,
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		};

		// Create a vertex buffer
		m_VertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexArray.reset(Engine::VertexArray::Create());

		// Give buffer its layout
		Engine::BufferLayout layout = {
			{Engine::ShaderDataType::Float3, "a_Position"}
		};
		m_VertexBuffer->SetLayout(layout);

		// add buffer to the array 
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		Engine::RenderCommand::SetClearColor(0.0f, 1.0f, 0.0f, 1.0f);

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
		glm::mat4 vp = camera.GetViewProjectionMatrix();

		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_ViewProjection", vp);

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, m_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		m_Shader->SetUniformMat4("u_Model", model);

		m_VertexArray->Bind();
		Engine::RenderCommand::Draw(3);
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
			Engine::RenderCommand::SetViewPort(0, 0, width, height);

			// Update Camera
			m_CameraController.OnResize(
				(float)resizeEvent.GetWidth(),
				(float)resizeEvent.GetHeight()
			);

		}
	}

	void OnDetach()
	{}

private:
	std::unique_ptr<Engine::Shader> m_Shader;
	std::shared_ptr < Engine::VertexArray> m_VertexArray;
	std::shared_ptr<Engine::VertexBuffer> m_VertexBuffer;
	float m_Angle = 0.0f;

	Engine::CameraController m_CameraController;
};
