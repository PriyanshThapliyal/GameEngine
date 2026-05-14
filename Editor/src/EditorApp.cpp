#include "Engine.h"

#include <memory>

#include "EditorLayer.h"
#include "Scene/Scene.h"

namespace Editor
{
	class EditorApplication : public Engine::Application
	{
	public:
		EditorApplication()
			: Engine::Application("Editor")
		{
			m_Scene = std::make_unique<Engine::Scene>();
			PushLayer(new EditorLayer(m_Scene.get()));
		}

	private:
		std::unique_ptr<Engine::Scene> m_Scene;
	};
}

Engine::Application* Engine::CreateApplication()
{
	return new Editor::EditorApplication();
}
