#pragma once

#include <vector>
#include "Entity.h"
#include "glm/glm.hpp"

#include "../Renderer/Camera.h"

namespace Engine
{
	struct SimpleRenderData
	{
		glm::vec2 Position;
		glm::vec2 Size;
		glm::vec4 Color;
	};

	class Scene
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		void OnUpdate(float dt);
		void OnRender();

	private:
		std::vector<Entity> m_Entities; // IDs for entities in the scene
		std::unordered_map<uint32_t, SimpleRenderData> m_RenderData;
		Camera m_Camera;
	
	};
}
