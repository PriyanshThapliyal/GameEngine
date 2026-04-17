#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	struct TransformComponent
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
	};
}