#pragma once

namespace Editor
{
	enum class SceneState;

	class ToolbarPanel
	{
	public:
		bool OnImGuiRender(SceneState sceneState, bool& saveRequested, bool& loadRequested);
	};
}
