#pragma once

namespace Engine
{
	class Scene;
}

namespace Editor
{
	enum class SceneState;

	class StatisticsPanel
	{
	public:
		void OnImGuiRender(float dt, Engine::Scene& scene, SceneState sceneState);
	};
}
