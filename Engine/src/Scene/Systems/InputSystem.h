#pragma once

namespace Engine
{
	class Scene;

	class InputSystem
	{
	public:
		static void Update(Scene& scene, float deltaTime);
	};
}