#include "enpch.h"
#include "EditorLayer.h"
#include "../../..//Input/Input.h"
#include "../../../Input/KeyCode.h"
#include "../../../Events/Event.h"
#include "../../../../Scene/SceneSerializer.h"
#include "ImGui/imgui.h"

namespace Engine
{
	EditorLayer::EditorLayer(Scene* scene)
		:m_Scene(scene)
	{
	}

	void EditorLayer::OnAttach()
	{
		EN_CORE_TRACE("EditorLayer Attached");
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(float dt)
	{
		
	}

	void EditorLayer::OnEvent(Event& e)
	{
		// SAVE
		if (e.GetEventType() == EventType::KeyPressed && Input::IsKeyPressed(KeyCode::LeftControl) && Input::IsKeyPressed(KeyCode::S))
		{
			SaveScene();
			e.Handled = true;
		}

		//Test : Spawn Enemy
		if (!e.Handled && e.GetEventType() == EventType::KeyPressed && Input::IsKeyPressed(KeyCode::O) && !Input::IsKeyPressed(KeyCode::LeftControl))
		{
			// Spawn an enemy at a random position
			Entity enemy = m_Scene->CreateEntity("Enemy");

			EN_CORE_INFO("Spawned Enemy with ID: {0}", enemy.GetID());

			auto& tc = enemy.AddComponent<TransformComponent>();
			tc.Scale = { 2.0f, 2.0f, 0.0f };
			tc.Position = { 0.0f, 0.0f, 0.0f };
			auto& sc = enemy.AddComponent<SpriteRendererComponent>();
			sc.Color = { 1.0f, 0.0f, 0.6f, 1.0f };
			enemy.AddComponent<EnemyComponent>();
			enemy.AddComponent<VelocityComponent>();
			e.Handled = true;
		}

		// LOAD
		if (!e.Handled && e.GetEventType() == EventType::KeyPressed && Input::IsKeyPressed(KeyCode::LeftControl) && Input::IsKeyPressed(KeyCode::O))
		{
			LoadScene();
			e.Handled = true;
		}
	}

	void EditorLayer::SaveScene()
	{
		EN_CORE_INFO("Saving Scene...");
		SceneSerializer serializer(m_Scene);
		serializer.Serialize("Engine/assets/SceneData/scene1.json");
	}

	void EditorLayer::LoadScene()
	{
		m_Scene->Clear();
		EN_CORE_INFO("Loading Scene...");
		SceneSerializer serializer(m_Scene);
		serializer.Deserialize("Engine/assets/SceneData/scene1.json");

		bool hasCamera = false;

		for (auto& entity : m_Scene->GetView<CameraComponent>())
		{
			if (entity.GetComponent<CameraComponent>().Primary)
			{
				hasCamera = true;
				break;
			}
		}

		if (!hasCamera)
		{
			Entity cam = m_Scene->CreateEntity("Camera");
			cam.AddComponent<TransformComponent>();
			auto& cc = cam.AddComponent<CameraComponent>();
			cc.Primary = true;
		}
	}

	void EditorLayer::OnImGuiRender(float dt)
	{
		ImGui::Begin("Debug Panel");
		
		ImGui::Text("State %s", isPlaying ? "PLAY" : "EDITOR");

		if (ImGui::CollapsingHeader("Performance"))
		{
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.2f, 1.0f), "FPS: %.2f", 1.0f / dt);
			ImGui::TextColored(ImVec4(0.2f, 0.8f, 1.0f, 1.0f), "Delta Time: %.3f ms", dt * 1000.0f);

			ImGui::Text("CPU: %.1f%%", 0.0f); 
			ImGui::Text("GPU: %.1f%%", 0.0f); 
		}

		if (ImGui::CollapsingHeader("Scene Info"))
		{
			ImGui::Text("Scene Entity Count: %d", m_Scene->GetEntityCount());
		}

		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::Text("Mouse Position: (%.1f, %.1f)", Input::GetMousePosition().first, Input::GetMousePosition().second);
		}

		ImGui::End();


		// Hierarchy

		ImGui::Begin("Hierarchy");

		const auto& view = m_Scene->GetAllEntities();

		int index = 0;

		for (const Entity& entity : view)
		{
			ImGui::PushID(index++);

			auto& tag = entity.GetComponent<TagComponent>().Tag;

			std::string label =
				tag + " [" + std::to_string(entity.GetID()) + "]";

			bool selected = (m_selectedEntity == entity);

			if (ImGui::Selectable(label.c_str(), selected))
			{
				m_selectedEntity = entity;
			}

			ImGui::PopID();
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_selectedEntity = {};
		}

		ImGui::End();

		// Inspector

		ImGui::Begin("Inspector");
		
		if (!m_selectedEntity)
		{
			const auto& entities = m_Scene->GetAllEntities();
			if (!entities.empty())
				m_selectedEntity = entities[0];
		}

		if (m_selectedEntity)
		{
			ImGui::Text("Selected Entity ID: %d", m_selectedEntity.GetID());
			if (m_selectedEntity.HasComponent<TransformComponent>())
			{
				ImGui::Text("Transform Component:");
				auto& tc = m_selectedEntity.GetComponent<TransformComponent>();
				ImGui::DragFloat3("Position", &tc.Position.x, 0.1f);
				ImGui::DragFloat3("Scale", &tc.Scale.x, 0.1f);
				ImGui::DragFloat("Rotation", &tc.Rotation, 0.1f);
			}
			if (m_selectedEntity.HasComponent<SpriteRendererComponent>())
			{
				ImGui::Separator();
				ImGui::Text("Sprite Renderer Component:");
				auto& sc = m_selectedEntity.GetComponent<SpriteRendererComponent>();
				ImGui::ColorEdit4("Color", &sc.Color.x);
			}
		}
		else
		{
			ImGui::Text("No entity selected.");
		}

		ImGui::End();
		
	}

}
