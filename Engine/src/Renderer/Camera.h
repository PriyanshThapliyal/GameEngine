#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	class Camera
	{
	public:
		Camera(float left, float rignt, float bottom, float top, float nearClip, float farClip);

		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return m_Position; }
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

	};

}


// In general camera don't move at all it stays at a same place but the world moves around the camera 
// (Camera does move too and world moves opposite to the camera, and camera have its positon that we change in x y or z axis) 
// Veiw Matrix represent the cooridinates of the world currently wrt camera
// (View Matrix expresses the world as seen from the camera)
// viewMatrix = inverse(cameraTransform)
