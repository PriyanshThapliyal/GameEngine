#pragma once

#include "EditorCamera.h"
#include "Panels/InspectorPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/StatisticsPanel.h"
#include "Panels/ToolbarPanel.h"
#include "Panels/ViewportPanel.h"

#include "Engine/Core/LayerStack/Layer.h"
#include "Scene/Entity.h"

namespace Engine
{
	class Scene;
}

namespace Editor
{
	enum class SceneState
	{
		Edit = 0,
		Play = 1
	};

	class EditorLayer : public Engine::Layer
	{
	public:
		EditorLayer(Engine::Scene* scene);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnEvent(Engine::Event& e) override;
		void OnImGuiRender(float dt) override;

		void OnScenePlay();
		void OnSceneStop();

	private:
		void SaveScene();
		void LoadScene();

		void CreateDemoScene();
		void CreatePlayer();
		void CreateProps();
		void CreateGround();

	private:
		Engine::Scene* m_Scene = nullptr;
		Engine::Entity m_SelectedEntity;
		EditorCamera m_EditorCamera;
		SceneState m_SceneState = SceneState::Edit;

		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;
		StatisticsPanel m_StatisticsPanel;
		ToolbarPanel m_ToolbarPanel;
		ViewportPanel m_ViewportPanel;
	};
}
