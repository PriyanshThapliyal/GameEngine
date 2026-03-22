#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Core/Log.h"
#include "Renderer/Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	}

	void OnUpdate(float deltaTime) override
	{
		m_Angle += deltaTime;
	}

	void OnRender() override
	{	
		glClear(GL_COLOR_BUFFER_BIT);
		m_Shader->Bind();

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.1f, 0.1f, 0.3f));
		model = glm::rotate(model, m_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

		glm::mat4 mvp = projection * view * model;

		m_Shader->SetUniformMat4("u_MVP", mvp);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
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
	unsigned int m_VAO, m_VBO;
	float m_Angle = 0.0f;

};