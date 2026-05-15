#include "EditorLayer.h"

#include <glm/glm.hpp>

#include "Engine/Core/Log.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/KeyCode.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/ControlledComponent.h"
#include "Scene/Components/DragableComponent.h"
#include "Scene/Components/EnemyComponent.h"
#include "Scene/Components/PlayerComponent.h"
#include "Scene/Components/SpriteRendererComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/VelocityComponent.h"
#include "Scene/Scene.h"
#include "Scene/SceneSerializer.h"

#include "Renderer/Texture.h"

namespace Editor
{
	EditorLayer::EditorLayer(Engine::Scene* scene)
		: Engine::Layer("EditorLayer"), m_Scene(scene)
	{
	}

	void EditorLayer::OnAttach()
	{
		EN_CORE_TRACE("EditorLayer Attached");

		m_Scene->Init();
		Engine::Renderer2D::Init();
		Engine::RenderCommand::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		CreateDemoScene();
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(float dt)
	{
		if (m_SceneState == SceneState::Edit)
		{
			m_EditorCamera.OnUpdate(dt);
			m_Scene->OnEditorUpdate(dt, m_EditorCamera.GetViewProjectionMatrix());
		}
		else
		{
			m_Scene->OnRuntimeUpdate(dt);
		}
	}

	void EditorLayer::OnEvent(Engine::Event& e)
	{
		if (!e.Handled && e.GetEventType() == Engine::EventType::KeyPressed &&
			Engine::Input::IsKeyPressed(Engine::KeyCode::O) &&
			!Engine::Input::IsKeyPressed(Engine::KeyCode::LeftControl))
		{
			Engine::Entity enemy = m_Scene->CreateEntity("Enemy");

			EN_CORE_INFO("Spawned Enemy with ID: {0}", enemy.GetID());

			auto& tc = enemy.AddComponent<Engine::TransformComponent>();
			tc.Scale = { 2.0f, 2.0f, 0.0f };
			tc.Position = { 0.0f, 0.0f, 0.0f };

			auto& sc = enemy.AddComponent<Engine::SpriteRendererComponent>();
			sc.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
			sc.TexturePath = "Engine/assets/Textures/enemy.png";
			sc.Texture = std::make_shared<Engine::Texture>(sc.TexturePath);

			enemy.AddComponent<Engine::EnemyComponent>();
			enemy.AddComponent<Engine::VelocityComponent>();
			e.Handled = true;
		}

		m_EditorCamera.OnEvent(e);
	}

	void EditorLayer::OnImGuiRender(float dt)
	{
		m_StatisticsPanel.OnImGuiRender(dt, *m_Scene, m_SceneState);
		m_SceneHierarchyPanel.OnImGuiRender(*m_Scene, m_SelectedEntity);
		m_InspectorPanel.OnImGuiRender(m_SelectedEntity);
		m_ViewportPanel.OnImGuiRender();

		bool saveRequested = false;
		bool loadRequested = false;
		bool togglePlayRequested = m_ToolbarPanel.OnImGuiRender(m_SceneState, saveRequested, loadRequested);

		if (saveRequested)
			SaveScene();

		if (loadRequested)
			LoadScene();

		if (togglePlayRequested)
		{
			if (m_SceneState == SceneState::Edit)
				OnScenePlay();
			else
				OnSceneStop();
		}
	}

	void EditorLayer::OnScenePlay()
	{
		m_SceneState = SceneState::Play;
	}

	void EditorLayer::OnSceneStop()
	{
		m_SceneState = SceneState::Edit;
	}

	void EditorLayer::SaveScene()
	{
		EN_CORE_INFO("Saving Scene...");
		Engine::SceneSerializer serializer(m_Scene);
		serializer.Serialize("Engine/assets/SceneData/scene1.json");
	}

	void EditorLayer::LoadScene()
	{
		m_Scene->Clear();
		m_SelectedEntity = {};

		EN_CORE_INFO("Loading Scene...");
		Engine::SceneSerializer serializer(m_Scene);
		serializer.Deserialize("Engine/assets/SceneData/scene1.json");

		bool hasCamera = false;

		for (auto& entity : m_Scene->GetView<Engine::CameraComponent>())
		{
			if (entity.GetComponent<Engine::CameraComponent>().Primary)
			{
				hasCamera = true;
				break;
			}
		}

		if (!hasCamera)
		{
			Engine::Entity cam = m_Scene->CreateEntity("Camera");
			cam.AddComponent<Engine::TransformComponent>();
			auto& cc = cam.AddComponent<Engine::CameraComponent>();
			cc.Primary = true;
		}
	}

	void EditorLayer::CreateDemoScene()
	{
		Engine::Entity camera = m_Scene->CreateEntity("Main Camera");
		auto& tc = camera.GetComponent<Engine::TransformComponent>();
		tc.Position = { 0.0f, 0.0f, 0.0f };
		camera.AddComponent<Engine::CameraComponent>();

		CreateGround();
		CreatePlayer();
		CreateProps();
	}

	void EditorLayer::CreatePlayer()
	{
		Engine::Entity player = m_Scene->CreateEntity("Player");
		auto& tc = player.GetComponent<Engine::TransformComponent>();
		tc.Position = { 0.0f, 0.0f, 0.0f };
		tc.Scale = { 1.0f, 1.0f, 1.0f };

		auto& sc = player.AddComponent<Engine::SpriteRendererComponent>();
		sc.TexturePath = "Engine/assets/Textures/player.png";
		sc.Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		sc.Texture = std::make_shared<Engine::Texture>(sc.TexturePath);
		player.AddComponent<Engine::PlayerComponent>();
		player.AddComponent<Engine::VelocityComponent>();
		player.AddComponent<Engine::ControlledComponent>();
		player.AddComponent<Engine::DragableComponent>();
	}

	void EditorLayer::CreateGround()
	{
		Engine::Entity ground = m_Scene->CreateEntity("Ground");
		auto& tc = ground.GetComponent<Engine::TransformComponent>();
		tc.Position = { -10.0f, -10.0f, 0.0f };
		tc.Scale = { 20.0f, 20.0f, 1.0f };

		auto& sc = ground.AddComponent<Engine::SpriteRendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		sc.TexturePath = "Engine/assets/Textures/grass.png";
		sc.Texture = std::make_shared<Engine::Texture>(sc.TexturePath);
	}

	void EditorLayer::CreateProps()
	{
		for (int i = 0; i < 5; i++)
		{
			Engine::Entity crate = m_Scene->CreateEntity("Crate");
			auto& tc = crate.GetComponent<Engine::TransformComponent>();
			tc.Position = { -4.0f + i * 2.0f, -1.5f, 0.0f };
			tc.Scale = { 0.8f, 0.8f, 1.0f };

			auto& sc = crate.AddComponent<Engine::SpriteRendererComponent>(
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
			);
			sc.TexturePath = "Engine/assets/Textures/crate.png";
			sc.Texture = std::make_shared<Engine::Texture>(sc.TexturePath);
		}
	}
}
