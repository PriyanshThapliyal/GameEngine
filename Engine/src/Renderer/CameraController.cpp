#include "enpch.h"
#include "CameraController.h"
#include <GLFW/glfw3.h>
#include "../Engine/Input/Input.h"

namespace Engine {
	CameraController::CameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio),
		  m_Camera(
			-aspectRatio * m_ZoomLevel,
			aspectRatio* m_ZoomLevel,
			-m_ZoomLevel,
			m_ZoomLevel,
			-1.0f,
			1.0f
		  )
	{
	}

	void CameraController::OnUpdate(float deltaTime)
	{
		float velocity = m_CameraSpeed * deltaTime;

		if (Input::IsKeyPressed(KeyCode::A))
			m_CameraPosition.x += velocity;
		if (Input::IsKeyPressed(KeyCode::D))
			m_CameraPosition.x -= velocity;
		if (Input::IsKeyPressed(KeyCode::W))
			m_CameraPosition.y -= velocity;
		if (Input::IsKeyPressed(KeyCode::S))
			m_CameraPosition.y += velocity;

		m_Camera.SetPosition(m_CameraPosition);
	}
}