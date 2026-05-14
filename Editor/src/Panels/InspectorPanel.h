#pragma once

#include "Scene/Entity.h"

namespace Editor
{
	class InspectorPanel
	{
	public:
		void OnImGuiRender(Engine::Entity selectedEntity);
	};
}
