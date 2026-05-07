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
#include "Components/TagComponent.h"

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

		virtual void Remove(Entity entity) = 0;
		virtual bool Has(Entity entity) const = 0;
	};

	struct TransformComponent;

	template<typename T>
	class ComponentStorage : public IComponentStorage
	{
	public:
		std::unordered_map<uint32_t, T> Data;
		void Remove(Entity entity) override
		{
			Data.erase(entity.GetID());
		}
		bool Has(Entity entity) const override
		{
			return Data.find(entity.GetID()) != Data.end();
		}

		T& Get(Entity entity)
		{
			return Data.at(entity.GetID());
		}
	};

	class Scene
	{
	public:
		Entity CreateEntity(const std::string& name);
		void DestroyEntity(Entity entity);
		void Clear();
		void Init();
		void OnUpdate(float dt);
		void OnRender();

		void UpdateInput(float dt);
		void UpdateMovement(float dt);
		void UpdateDragging(float dt);
		void UpdateEnemy(float dt);
		void UpdateCollision(float dt);

		int GetEntityCount() const { return static_cast<int>(m_Entities.size()); }
		
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

			for (Entity entity : m_Entities)
			{
				if ((entity.HasComponent<Components>() && ...))
					result.push_back(entity);
			}

			return result;
		}

		bool HasEntity(Entity entity) const
		{
			return std::find(m_Entities.begin(), m_Entities.end(), entity) != m_Entities.end();
		}

		const std::vector<Entity>& GetAllEntities() const;

	private:
		std::vector<Entity> m_Entities; 
		std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> m_ComponentStores;
		uint32_t m_NextEntityID = 1; 
		Entity m_SelectedEntity;
	};
}

#include "Entity.inl"
