#pragma once

namespace Engine
{
	class Scene;

	class CollisionSystem
	{
	public:
		static void Update(Scene& scene, float deltaTime);
	};
}
