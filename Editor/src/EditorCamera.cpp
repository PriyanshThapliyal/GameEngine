#include "EditorCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Input/Input.h"
#include "Engine/Input/KeyCode.h"
#include "Engine/Events/MouseEvent.h"

namespace Editor
{
	EditorCamera::EditorCamera()
	{
		UpdateProjection();
		UpdateView();
	}

	void EditorCamera::OnUpdate(float dt)
	{
		float speed = m_MoveSpeed * dt;

		if (Engine::Input::IsKeyPressed(Engine::KeyCode::A))
			m_Position.x -= speed;

		if (Engine::Input::IsKeyPressed(Engine::KeyCode::D))
			m_Position.x += speed;

		if (Engine::Input::IsKeyPressed(Engine::KeyCode::W))
			m_Position.y += speed;

		if (Engine::Input::IsKeyPressed(Engine::KeyCode::S))
			m_Position.y -= speed;

		UpdateView();
	}

	void EditorCamera::OnEvent(Engine::Event& e)
	{
		Engine::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Engine::MouseScrolledEvent>(
			[this](Engine::MouseScrolledEvent& e)
			{
				OnMouseScrolled(e.GetYOffset());
				return false;
			});
	}

	void EditorCamera::UpdateProjection()
	{
		float aspectRatio = 16.0f / 9.0f;
		float left = -aspectRatio * m_Zoom;
		float right = aspectRatio * m_Zoom;
		float top = m_Zoom;
		float bottom = -m_Zoom;

		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

	void EditorCamera::UpdateView()
	{
		m_View = glm::translate(glm::mat4(1.0f), -m_Position);
	}

	void EditorCamera::OnMouseScrolled(float yOffset)
	{
		m_Zoom -= yOffset * 0.25f;

		if (m_Zoom < 0.1f)
			m_Zoom = 0.1f;

		UpdateProjection();
	}
}
