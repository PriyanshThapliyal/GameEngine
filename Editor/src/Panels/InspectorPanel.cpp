#include "Panels/InspectorPanel.h"

#include "ImGui/imgui.h"
#include "Scene/Components/EnemyComponent.h"
#include "Scene/Components/PlayerComponent.h"
#include "Scene/Components/SpriteRendererComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/VelocityComponent.h"

namespace Editor
{
	void InspectorPanel::OnImGuiRender(Engine::Entity selectedEntity)
	{
		ImGui::Begin("Inspector");

		if (selectedEntity)
		{
			ImGui::Text("Selected Entity ID: %d", selectedEntity.GetID());

			if (selectedEntity.HasComponent<Engine::TransformComponent>())
			{
				auto& tc = selectedEntity.GetComponent<Engine::TransformComponent>();

				if (ImGui::CollapsingHeader("Transform"))
				{
					ImGui::DragFloat3("Position", &tc.Position.x, 0.1f);
					ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);
					ImGui::DragFloat("Rotation", &tc.Rotation, 0.1f);
				}
			}

			if (selectedEntity.HasComponent<Engine::SpriteRendererComponent>())
			{
				auto& sc = selectedEntity.GetComponent<Engine::SpriteRendererComponent>();

				if (ImGui::CollapsingHeader("Sprite Renderer"))
					ImGui::ColorEdit4("Color", &sc.Color.x);
			}

			if (selectedEntity.HasComponent<Engine::VelocityComponent>())
			{
				auto& vc = selectedEntity.GetComponent<Engine::VelocityComponent>();

				if (ImGui::CollapsingHeader("Velocity"))
				{
					ImGui::DragFloat("Velocity X", &vc.Velocity.x, 0.1f);
					ImGui::DragFloat("Velocity Y", &vc.Velocity.y, 0.1f);
					ImGui::DragFloat("Speed", &vc.Speed, 0.1f);
				}
			}

			if (selectedEntity.HasComponent<Engine::PlayerComponent>())
			{
				auto& pc = selectedEntity.GetComponent<Engine::PlayerComponent>();

				if (ImGui::CollapsingHeader("Player Component"))
					ImGui::DragFloat("Speed##Player", &pc.Speed, 0.1f);
			}

			if (selectedEntity.HasComponent<Engine::EnemyComponent>())
			{
				auto& ec = selectedEntity.GetComponent<Engine::EnemyComponent>();

				if (ImGui::CollapsingHeader("Enemy Component"))
					ImGui::DragFloat("Speed##Enemy", &ec.Speed, 0.1f);
			}
		}
		else
		{
			ImGui::Text("No entity selected.");
		}

		ImGui::End();
	}
}
