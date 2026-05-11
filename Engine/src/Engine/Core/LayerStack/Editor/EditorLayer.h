#pragma once

#include "../Layer.h"
#include "../../../../Scene/Scene.h"
#include "EditorCamera.h"

namespace Engine
{
	enum class SceneState
	{
		Edit = 0,
		Play = 1
	};
	
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(Scene* scene);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnEvent(Event& e) override;

		void OnScenePlay();
		void OnSceneStop();

		void OnImGuiRender(float dt) override;

	private:
		void SaveScene();
		void LoadScene();

	private:
		Scene* m_Scene;
		bool isPlaying = false;
		Entity m_selectedEntity;
		EditorCamera m_EditorCamera;
		SceneState m_SceneState = SceneState::Edit;
	};

	
}