#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Entity.h"
#include "glm/glm.hpp"

#include "../Renderer/Camera.h"
#include "../Renderer/Renderer2D.h"

#include "../Engine/Input/Input.h"

// Components
#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/CameraComponent.h"
#include "Components/ControlledComponent.h"
#include "Components/DragableComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"

// Systems
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/EnemyAISystem.h"
#include "Systems/DragSystem.h"
#include "Systems/CollisionSystem.h"

namespace Engine
{
	struct IComponentStorage
	{
		virtual ~IComponentStorage() = default;
	};

	struct TransformComponent;

	template<typename T>
	struct ComponentStorage : IComponentStorage
	{
		std::unordered_map<uint32_t, T> Data;
	};

	class Scene
	{
	public:
		Entity CreateEntity();
		void DestroyEntity(Entity entity);
		void Init();
		void OnUpdate(float dt);
		void OnRender();

		void UpdateInput(float dt);
		void UpdateMovement(float dt);
		void UpdateDragging(float dt);
		void UpdateEnemy(float dt);
		void UpdateCollision(float dt);

		template<typename T>
		ComponentStorage<T>* GetStorage()
		{
			std::type_index index(typeid(T));

			if (m_ComponentStores.find(index) == m_ComponentStores.end())
			{
				m_ComponentStores[index] = std::make_unique<ComponentStorage<T>>();
			}

			return static_cast<ComponentStorage<T>*>(m_ComponentStores[index].get());
		}

		template<typename... Components>
		std::vector<Entity> GetView()
		{
			std::vector<Entity> result;
			result.reserve(m_Entities.size());

			for (auto& entity : m_Entities)
			{
				if ((entity.HasComponent<Components>() && ...))
					result.push_back(entity);
			}

			return result;
		}

	private:
		std::vector<Entity> m_Entities; // IDs for entities in the scene
		std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> m_ComponentStores;
	
	};
}

#include "Entity.inl"
