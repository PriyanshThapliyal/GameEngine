#include "Panels/StatisticsPanel.h"

#include "EditorLayer.h"
#include "ImGui/imgui.h"
#include "Engine/Input/Input.h"
#include "Scene/Scene.h"

namespace Editor
{
	void StatisticsPanel::OnImGuiRender(float dt, Engine::Scene& scene, SceneState sceneState)
	{
		ImGui::Begin("Debug Panel");

		ImGui::Text("State %s", sceneState == SceneState::Play ? "PLAY" : "EDITOR");

		if (ImGui::CollapsingHeader("Performance"))
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.2f, 1.0f), "FPS: %.2f", 1.0f / dt);
			ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "Delta Time: %.3f ms", dt * 1000.0f);
			ImGui::Text("CPU: %.1f%%", 0.0f);
			ImGui::Text("GPU: %.1f%%", 0.0f);
		}

		if (ImGui::CollapsingHeader("Scene Info"))
			ImGui::Text("Scene Entity Count: %d", scene.GetEntityCount());

		if (ImGui::CollapsingHeader("Input"))
		{
			auto [mouseX, mouseY] = Engine::Input::GetMousePosition();
			ImGui::Text("Mouse Position: (%.1f, %.1f)", mouseX, mouseY);
		}

		ImGui::End();
	}
}
