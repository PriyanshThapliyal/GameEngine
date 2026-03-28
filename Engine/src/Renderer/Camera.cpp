#include "enpch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Engine
{
	Camera::Camera(float left, float right, float bottom, float top, float far, float near)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, far, near);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

<<<<<<< HEAD
	void Camera::SetProjection(float left, float right, float bottom, float top, float far, float near)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

=======
>>>>>>> 6cd911df5498deef757be6574883a57cc62c178c
	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		// Inverse for camera
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}