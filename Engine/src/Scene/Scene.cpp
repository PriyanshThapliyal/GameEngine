#include "enpch.h"
#include "Scene.h"
#include "Entity.h"
#include "../Renderer/Renderer2D.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"

namespace Engine
{
	Entity Scene::CreateEntity()
	{
		static uint32_t s_NextID = 1;

		Entity entity(s_NextID++, this);
		m_Entities.push_back(entity);

		entity.AddComponent<TransformComponent>();
		entity.AddComponent<SpriteRendererComponent>();

		return entity;
	}

	void Scene::OnUpdate(float dt)
	{

	}

	void Scene::OnRender(const Camera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto transformStorage = GetStorage<TransformComponent>();
		auto spriteStorage = GetStorage<SpriteRendererComponent>();

		for (auto& [entityID, transform] : transformStorage->Data)
		{
			if (spriteStorage->Data.find(entityID) != spriteStorage->Data.end())
			{
				auto& sprite = spriteStorage->Data[entityID];

				Renderer2D::DrawQuad(
					transform.Position,
					transform.Scale,
					sprite.Color
				);
			}
		}

		Renderer2D::FlushAndReset();
	}

	void Scene::DestroyEntity(Entity entity)
	{
		
	}

}