#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
	};
}