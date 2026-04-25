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
		glm::vec2 directon = { 0.0f, 0.0f };

		if (Input::IsKeyPressed(KeyCode::A))
			directon.x -= 1.0f;
		if (Input::IsKeyPressed(KeyCode::D))
			directon.x += 1.0f;
		if (Input::IsKeyPressed(KeyCode::W))
			directon.y += 1.0f;
		if (Input::IsKeyPressed(KeyCode::S))
			directon.y -= 1.0f;

		if(glm::length(directon) > 0.0f)
			directon = glm::normalize(directon);

		m_CameraPosition += glm::vec3(directon, 0.0f) * m_CameraSpeed * deltaTime;
		m_Camera.SetPosition(m_CameraPosition);
	}

	void CameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		
		m_Camera.SetProjection(
			-m_AspectRatio,
			 m_AspectRatio,
			-1.0f,
			 1.0f,
			-1.0f,
			 1.0f
		);
	}
}