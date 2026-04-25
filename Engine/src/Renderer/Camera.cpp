#include "enpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	Camera::Camera()
	{
		m_ViewMatrix = glm::mat4(1.0f);
		SetProjection(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
	}

	Camera::Camera(float left, float right, float bottom, float top, float near, float far)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetProjection(float left, float right, float bottom, float top, float near, float far)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		// Inverse for camera
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}