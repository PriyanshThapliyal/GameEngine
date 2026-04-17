#pragma once

#include <cstdint>
#include <utility>

namespace Engine
{
	template<typename T>
	struct ComponentStorage;

	class Scene;

	class Entity
	{
	public:
		Entity();
		Entity(uint32_t id, Scene* scene);
		
		uint32_t GetID() const;

		operator bool() const;

		// ECS API
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		T& GetComponent();

		template<typename T>
		bool HasComponent() const;

		template<typename T>
		void RemoveComponent();

	private:
		uint32_t m_ID;
		Scene* m_Scene = nullptr;
	};
}
