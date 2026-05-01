#pragma once

#include "../Engine/Core/Layer.h"
#include "../Scene/Scene.h"

namespace Engine
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer(Scene* scene);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnEvent(Event& e) override;

	private:
		void SaveScene();
		void LoadScene();

	private:
		Scene* m_Scene;
	};
}