#include "Panels/SceneHierarchyPanel.h"

#include <string>

#include "ImGui/imgui.h"
#include "Scene/Scene.h"
#include "Scene/Components/TagComponent.h"

namespace Editor
{
	void SceneHierarchyPanel::OnImGuiRender(Engine::Scene& scene, Engine::Entity& selectedEntity)
	{
		ImGui::Begin("Hierarchy");

		const auto& entities = scene.GetAllEntities();
		int index = 0;

		for (const Engine::Entity& entity : entities)
		{
			ImGui::PushID(index++);

			auto& tag = entity.GetComponent<Engine::TagComponent>().Tag;
			std::string label = tag + " [" + std::to_string(entity.GetID()) + "]";
			bool selected = (selectedEntity == entity);

			if (ImGui::Selectable(label.c_str(), selected))
				selectedEntity = entity;

			ImGui::PopID();
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			selectedEntity = {};

		ImGui::End();
	}
}
