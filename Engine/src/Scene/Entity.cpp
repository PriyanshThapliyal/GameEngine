#include "enpch.h"
#include "Entity.h"
#include "Scene.h"

namespace Engine
{
	Entity::Entity(uint32_t id, Scene* scene)
		: m_ID(id), m_Scene(scene)
	{

	}
}
