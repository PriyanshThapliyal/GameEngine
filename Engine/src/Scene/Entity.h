#pragma once

namespace Engine
{
	class Scene;

	class Entity
	{
	public:
		Entity() = default;
		Entity(uint32_t id, Scene* scene);
			
		uint32_t GetID() const { return m_ID; }

		operator bool() const { return m_ID != 0; }
	private:
		uint32_t m_ID;
		Scene* m_Scene = nullptr;
	};
}
