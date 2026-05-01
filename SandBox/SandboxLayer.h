#pragma once

#include <memory>
#include "Engine.h"
#include "Engine/Core/Layer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Renderer/Shader.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"

#include "Scene/Scene.h"
#include "Scene/Entity.h"

#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/SpriteRendererComponent.h"
#include "Scene/Components/VelocityComponent.h"
#include "Scene/Components/DragableComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/ControlledComponent.h"


class SandboxLayer : public Engine::Layer
{
public:
	SandboxLayer()
		: Layer("SandboxLayer")

	{}

	void OnAttach() override
	{
		EN_CORE_WARN("SandboxLayer Attached");

		m_Scene = Engine::Application::Get().GetScene();
		m_Scene->Init();

		Engine::Renderer2D::Init();
		Engine::RenderCommand::SetClearColor(0.1f,0.1f,0.1f,1.0f);
	}

	void OnUpdate(float deltaTime) override
	{
		m_Angle += deltaTime;
		m_Scene->OnUpdate(deltaTime);

	}

	void OnRender() override
	{
		Engine::RenderCommand::Clear();

		m_Scene->OnRender();
	}

	void OnEvent(Engine::Event& e) override
	{
		
	}

	void OnDetach()
	{}

private:
	float m_Angle = 0.0f;
	std::unique_ptr<Engine::Texture> m_Texture;
	Engine::Scene* m_Scene = nullptr;
};
