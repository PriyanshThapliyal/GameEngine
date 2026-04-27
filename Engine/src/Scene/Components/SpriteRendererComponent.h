#pragma once

#include <glm/glm.hpp>

namespace Engine
{
	struct SpriteRendererComponent
	{
		glm::vec4 Color = { 1.0f, 0.0f, 0.0f, 1.0f }; // tint
		std::shared_ptr<Texture> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;

		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};
}