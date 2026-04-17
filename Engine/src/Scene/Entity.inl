#pragma once

#include "Scene.h"

namespace Engine
{
	inline Entity::Entity() : m_ID(0), m_Scene(nullptr) {}
	inline Entity::Entity(uint32_t id, Scene* scene) : m_ID(id), m_Scene(scene) {}
	inline uint32_t Entity::GetID() const { return m_ID; }
	inline Entity::operator bool() const { return m_ID != 0; }

	// ECS API definitions
	template<typename T, typename... Args>
	T& Entity::AddComponent(Args&&... args)
	{
		auto storage = m_Scene->template GetStorage<T>();
		auto [it, success] = storage->Data.emplace(m_ID, T(std::forward<Args>(args)...));
		return it->second;
	}

	template<typename T>
	T& Entity::GetComponent()
	{
		auto storage = m_Scene->template GetStorage<T>();
		return storage->Data.at(m_ID);
	}

	template<typename T>
	bool Entity::HasComponent() const
	{
		auto storage = m_Scene->template GetStorage<T>();
		return storage->Data.find(m_ID) != storage->Data.end();
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		auto storage = m_Scene->template GetStorage<T>();
		storage->Data.erase(m_ID);
	}
}

#include "Entity.h"
