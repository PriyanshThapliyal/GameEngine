#include "enpch.h"
#include "Scene.h"
#include "Entity.h"
#include "../Renderer/Renderer2D.h"

#include "../Engine/Input/Input.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/CameraComponent.h"
#include "Components/ControlledComponent.h"

namespace Engine
{
	Entity Scene::CreateEntity()
	{
		static uint32_t s_NextID = 1;

		Entity entity(s_NextID++, this);
		m_Entities.push_back(entity);

		entity.AddComponent<TransformComponent>();

		return entity;
	}

	void Scene::Init()
	{
		EN_CORE_INFO("Initializing Scene...");
		Entity camera = CreateEntity();
		
		camera.AddComponent<VelocityComponent>();
		camera.AddComponent<CameraComponent>();
		camera.AddComponent<ControlledComponent>();

		camera.GetComponent<CameraComponent>().Primary = true;


		Entity quad = CreateEntity();

		quad.AddComponent<SpriteRendererComponent>();
		
		quad.GetComponent<SpriteRendererComponent>().Color = { 0.2f, 0.3f, 0.8f, 1.0f };

		quad.GetComponent<TransformComponent>().Position = { 0.0f, 0.0f, 0.0f };
		quad.GetComponent<TransformComponent>().Scale = { 1.0f, 1.0f, 1.0f };
	}

	void Scene::OnUpdate(float dt)
	{
		for (auto entity : m_Entities)
		{

			// Handle camera movement
			if (entity.HasComponent<ControlledComponent>() &&
				entity.HasComponent<VelocityComponent>())
			{
				auto& control = entity.GetComponent<ControlledComponent>();
				if (!control.IsControlled) continue;

				auto& velocity = entity.GetComponent<VelocityComponent>();
				auto& cam = entity.GetComponent<CameraComponent>();
				
				if (!cam.Primary) continue;

				velocity.Velocity = { 0.0f , 0.0f };

				if (Input::IsKeyPressed(KeyCode::D)) velocity.Velocity.x += 1.0f;
				if (Input::IsKeyPressed(KeyCode::A)) velocity.Velocity.x -= 1.0f;
				if (Input::IsKeyPressed(KeyCode::W)) velocity.Velocity.y += 1.0f;
				if (Input::IsKeyPressed(KeyCode::S)) velocity.Velocity.y -= 1.0f;

				if(glm::length(velocity.Velocity) > 0.0f)
					velocity.Velocity = glm::normalize(velocity.Velocity) * velocity.Speed;
			}

			// Update position based on velocity
			if (entity.HasComponent<TransformComponent>() &&
				entity.HasComponent<VelocityComponent>())
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& velocity = entity.GetComponent<VelocityComponent>();
			
				transform.Position += glm::vec3(velocity.Velocity * dt, 0.0f);
			}
		}

	}

	void Scene::OnRender()
	{
		Camera* mainCamera = nullptr;
		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };

		auto cameraStorage = GetStorage<CameraComponent>();
		auto transformStorage = GetStorage<TransformComponent>();

		for (auto& [entityID, cam] : cameraStorage->Data)
		{
			if (cam.Primary)
			{
				mainCamera = &cam.Camera;

				if (transformStorage->Data.find(entityID) != transformStorage->Data.end())
				{
					cameraPosition = transformStorage->Data[entityID].Position;
				}
				break;
			}
		}

		if (!mainCamera) return;

		mainCamera->SetPosition(cameraPosition);
		
		Renderer2D::BeginScene(*mainCamera);

		auto spriteStorage = GetStorage<SpriteRendererComponent>();

		for (auto& [entityID, transform] : transformStorage->Data)
		{
			auto it = spriteStorage->Data.find(entityID);
			if (it != spriteStorage->Data.end())
			{
				auto& sprite = it->second;

				Renderer2D::DrawQuad(
					transform.Position,
					transform.Scale,
					sprite.Color
				);
			}
		}

		Renderer2D::FlushAndReset();
	}

	void Scene::DestroyEntity(Entity entity)
	{
		
	}

}