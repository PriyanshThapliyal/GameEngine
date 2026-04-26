#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	struct DragableComponent
	{
		bool IsDragging = false;
		glm::vec2 Offset{ 0.0f }; // Move offset inside object when dragging
	};
}