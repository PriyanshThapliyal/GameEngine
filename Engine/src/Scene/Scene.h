#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "Entity.h"
#include "glm/glm.hpp"

#include "../Renderer/Camera.h"

namespace Engine
{
	struct IComponentStorage
	{
		virtual ~IComponentStorage() = default;
	};

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

		void OnUpdate(float dt);
		void OnRender(const Camera& camera);

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

	private:
		std::vector<Entity> m_Entities; // IDs for entities in the scene
		std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> m_ComponentStores;
	
	};
}

#include "Entity.inl"
