#pragma once

#include <string>
#include "Scene.h"

namespace Engine
{
	class SceneSerializer
	{
	public:
		SceneSerializer(Scene* scene);	
		~SceneSerializer();

		void Serialize(const std::string& filepath);
		void Deserialize(const std::string& filepath);

	private:
		Scene* m_Scene;
	};
}