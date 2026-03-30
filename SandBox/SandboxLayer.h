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
#include "Renderer/VertexArray.h"

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
		m_Shader = std::make_unique<Engine::Shader>(
			"Engine/assets/Shaders/triangle.vert",
			"Engine/assets/Shaders/triangle.frag"
		);
		EN_CORE_WARN("Shader Compiled");

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,
		    -0.5f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f
		};

		uint32_t indices[] = {
			0 , 1, 2,
			2, 3, 0
		};

		auto indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));


		// Create a vertex buffer
		m_VertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexArray.reset(Engine::VertexArray::Create());

		// Give buffer its layout
		Engine::BufferLayout layout = {
			{Engine::ShaderDataType::Float3, "aPos"}
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->SetIndexBuffer(std::shared_ptr<Engine::IndexBuffer>(indexBuffer));

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
		Engine::RenderCommand::DrawIndexed(m_VertexArray);
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
	std::unique_ptr<Engine::Shader> m_Shader;
	std::shared_ptr < Engine::VertexArray> m_VertexArray;
	std::shared_ptr<Engine::VertexBuffer> m_VertexBuffer;
	float m_Angle = 0.0f;

	Engine::CameraController m_CameraController;
};
