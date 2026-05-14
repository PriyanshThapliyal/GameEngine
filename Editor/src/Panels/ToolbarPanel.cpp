#include "Panels/ToolbarPanel.h"

#include "EditorLayer.h"
#include "ImGui/imgui.h"

namespace Editor
{
	bool ToolbarPanel::OnImGuiRender(SceneState sceneState, bool& saveRequested, bool& loadRequested)
	{
		bool togglePlayRequested = false;
		saveRequested = false;
		loadRequested = false;

		ImGui::Begin("Toolbar");

		if (ImGui::Button("Save Scene"))
			saveRequested = true;

		ImGui::SameLine();

		if (ImGui::Button("Load Scene"))
			loadRequested = true;

		if (ImGui::Button(sceneState == SceneState::Edit ? "Play" : "Stop"))
			togglePlayRequested = true;

		ImGui::End();

		return togglePlayRequested;
	}
}
