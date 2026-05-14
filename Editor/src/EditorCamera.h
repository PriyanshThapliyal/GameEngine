#pragma once

#include <glm/glm.hpp>

#include "Engine/Events/Event.h"

namespace Editor
{
	class EditorCamera
	{
	public:
		EditorCamera();

		void OnUpdate(float dt);
		void OnEvent(Engine::Event& e);
		void OnMouseScrolled(float yOffset);

		glm::mat4 GetViewProjectionMatrix() const { return m_Projection * m_View; }

	private:
		void UpdateProjection();
		void UpdateView();

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
		float m_Zoom = 10.0f;
		float m_MoveSpeed = 5.0f;
	};
}
