#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Core/Log.h"
#include "Renderer/Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/RenderCommand.h"
#include "Renderer/Buffer.h"
#include <memory>
#include "../Engine/src/Renderer/VertexArray.h"

class SandboxLayer : public Engine::Layer
{
public:
	SandboxLayer()
		: Layer("SandboxLayer") {
	}

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
	}

	void OnRender() override
	{	
		Engine::RenderCommand::Clear();
		m_Shader->Bind();

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.1f, 0.1f, 0.0f));
		model = glm::rotate(model, m_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

		glm::mat4 mvp = projection * view * model;

		m_Shader->SetUniformMat4("u_MVP", mvp);
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
	}

	void OnDetach()
	{
	}

private:
	std::unique_ptr<Engine::Shader> m_Shader;
	std::shared_ptr < Engine::VertexArray> m_VertexArray;
	std::shared_ptr<Engine::VertexBuffer> m_VertexBuffer;
	float m_Angle = 0.0f;

};