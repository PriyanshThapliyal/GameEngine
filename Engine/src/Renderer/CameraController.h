#pragma once

#include "Camera.h"

namespace Engine
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio);

		void OnUpdate(float deltaTime);

		Camera& GetCamera() { return m_Camera; }

	private:
		float m_AspectRatio;
		float m_CameraSpeed = 2.0f;
		float m_ZoomLevel = 1.0f;

		glm::vec3 m_CameraPosition = { 0.0f , 0.0f , 0.0f };

		Camera m_Camera;
	};
}