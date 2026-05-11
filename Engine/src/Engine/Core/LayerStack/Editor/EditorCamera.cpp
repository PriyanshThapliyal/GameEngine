#include "enpch.h"
#include "EditorCamera.h"
#include "../../../Input/Input.h"
#include "../../../Input/KeyCode.h"
#include "../../../Events/Event.h"
#include "../../../Events/MouseEvent.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../../Log.h"

namespace Engine
{
	EditorCamera::EditorCamera()
	{
		UpdateProjection();
		UpdateView();
	}

	void EditorCamera::OnUpdate(float dt)
	{
		float speed = m_MoveSpeed * dt;

		if (Input::IsKeyPressed(KeyCode::A))
			m_Position.x -= speed;

		if (Input::IsKeyPressed(KeyCode::D))
			m_Position.x += speed;

		if (Input::IsKeyPressed(KeyCode::W))
			m_Position.y += speed;

		if (Input::IsKeyPressed(KeyCode::S))
			m_Position.y -= speed;

		EditorCamera::UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>(
			[this](MouseScrolledEvent& e)
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
		float top =  m_Zoom;
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
		EditorCamera::UpdateProjection();
	}
}