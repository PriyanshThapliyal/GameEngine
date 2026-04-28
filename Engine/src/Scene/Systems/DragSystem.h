#pragma once

#include "glm/glm.hpp"
#include "../Components/TransformComponent.h"
#include "../Components/DragableComponent.h"

namespace Engine
{
	class Scene;

	class DragSystem
	{
	public:
		static bool IsMouseOver(const TransformComponent& transform, glm::vec2 mousePos);
		static void Update(Scene& scene, float dt);
	};
}