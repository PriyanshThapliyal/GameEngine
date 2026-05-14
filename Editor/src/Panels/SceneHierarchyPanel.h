#pragma once

#include "Scene/Entity.h"

namespace Engine
{
	class Scene;
}

namespace Editor
{
	class SceneHierarchyPanel
	{
	public:
		void OnImGuiRender(Engine::Scene& scene, Engine::Entity& selectedEntity);
	};
}
