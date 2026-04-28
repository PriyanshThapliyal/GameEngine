#pragma once

namespace Engine
{
	class Scene;

	class MovementSystem
	{
	public:
		static void Update(Scene& scene, float deltaTime);
	};
}

