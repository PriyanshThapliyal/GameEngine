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
#include "Components/DragableComponent.h"

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
		Entity camera = CreateEntity();

		camera.AddComponent<VelocityComponent>();
		camera.AddComponent<CameraComponent>();
		//camera.AddComponent<ControlledComponent>();

		camera.GetComponent<CameraComponent>().Primary = true;


		Entity quad = CreateEntity();

		quad.AddComponent<SpriteRendererComponent>();
		quad.AddComponent<DragableComponent>();
		quad.AddComponent<VelocityComponent>();
		quad.AddComponent<ControlledComponent>();

		quad.GetComponent<SpriteRendererComponent>().Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		quad.GetComponent<DragableComponent>().IsDragging = false;
		quad.GetComponent<ControlledComponent>().IsControlled = true;

		quad.GetComponent<TransformComponent>().Position = { 5.0f, 0.0f, 0.0f };
		quad.GetComponent<TransformComponent>().Scale = { 0.5f, 0.70f, 1.0f };
	}

	void Scene::OnUpdate(float dt)
	{
		Scene::UpdateInput(dt);
		Scene::UpdateDragging(dt);
		Scene::UpdateMovement(dt);

	}

	void Scene::OnRender()
	{
		Camera* mainCamera = nullptr;
		glm::vec3 cameraPosition{ 0.0f };

		auto cameraStorage = GetStorage<CameraComponent>();
		auto transformStorage = GetStorage<TransformComponent>();

		for (auto& [entityID, cam] : cameraStorage->Data)
		{
			if (!cam.Primary) continue;

			mainCamera = &cam.Camera;

			auto it = transformStorage->Data.find(entityID);

			if (it != transformStorage->Data.end())
			{
				cameraPosition = it->second.Position;
			}
			break;
		}

		if (!mainCamera) return;

		mainCamera->SetPosition(cameraPosition);
		
		Renderer2D::BeginScene(*mainCamera);

		auto spriteStorage = GetStorage<SpriteRendererComponent>();

		for (auto& entity : GetView<TransformComponent, SpriteRendererComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteRendererComponent>();
			
			Renderer2D::DrawQuad(
					transform.Position,
					transform.Scale,
					sprite.Color
				);
		}

		Renderer2D::FlushAndReset();
	}

	void Scene::UpdateInput(float dt) 
	{
		// Handle camera input (only the primary camera should respond)
		for (auto entity : GetView<ControlledComponent, VelocityComponent, CameraComponent>())
		{
			auto& control = entity.GetComponent<ControlledComponent>();
			if (!control.IsControlled) continue;

			auto& cam = entity.GetComponent<CameraComponent>();
			if (!cam.Primary) continue;

			auto& velocity = entity.GetComponent<VelocityComponent>();

			velocity.Velocity = { 0.0f, 0.0f };

			if (Input::IsKeyPressed(KeyCode::D)) velocity.Velocity.x += 1.0f;
			if (Input::IsKeyPressed(KeyCode::A)) velocity.Velocity.x -= 1.0f;
			if (Input::IsKeyPressed(KeyCode::W)) velocity.Velocity.y += 1.0f;
			if (Input::IsKeyPressed(KeyCode::S)) velocity.Velocity.y -= 1.0f;

			if (glm::length(velocity.Velocity) > 0.0f)
				velocity.Velocity = glm::normalize(velocity.Velocity) * velocity.Speed;
		}

		// Handle other controlled entities without camera
		for (auto entity : GetView<ControlledComponent, VelocityComponent>())
		{
			auto& control = entity.GetComponent<ControlledComponent>();
			if (!control.IsControlled) continue;

			// Skip if this entity has a camera (already handled above)
			if (entity.HasComponent<CameraComponent>()) continue;

			auto& velocity = entity.GetComponent<VelocityComponent>();

			velocity.Velocity = { 0.0f, 0.0f };

			if (Input::IsKeyPressed(KeyCode::D)) velocity.Velocity.x += 1.0f;
			if (Input::IsKeyPressed(KeyCode::A)) velocity.Velocity.x -= 1.0f;
			if (Input::IsKeyPressed(KeyCode::W)) velocity.Velocity.y += 1.0f;
			if (Input::IsKeyPressed(KeyCode::S)) velocity.Velocity.y -= 1.0f;

			if (glm::length(velocity.Velocity) > 0.0f)
				velocity.Velocity = glm::normalize(velocity.Velocity) * velocity.Speed;
		}
	}
	
	void Scene::UpdateMovement(float dt)
	{
		auto allEntities = GetView<TransformComponent, VelocityComponent>();

		for (auto entity : allEntities)
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& velocity = entity.GetComponent<VelocityComponent>();

			transform.Position += glm::vec3(velocity.Velocity * dt, 0.0f);
		}
	}

	bool Scene::IsMouseOver(const TransformComponent& transform, glm::vec2 mousePos)
	{
		glm::vec2 min = {
			transform.Position.x - transform.Scale.x * 0.5f,
			transform.Position.y - transform.Scale.y * 0.5f
		};

		glm::vec2 max = {
			transform.Position.x + transform.Scale.x * 0.5f,
			transform.Position.y + transform.Scale.y * 0.5f
		};

		return mousePos.x >= min.x && mousePos.x <= max.x && 
			   mousePos.y >= min.y && mousePos.y <= max.y;
	}

	void Scene::UpdateDragging(float dt)
	{
		// Get the primary camera
		Camera* mainCamera = nullptr;
		glm::vec3 cameraPosition{ 0.0f };

		auto cameraStorage = GetStorage<CameraComponent>();
		auto transformStorage = GetStorage<TransformComponent>();

		for (auto& [entityID, cam] : cameraStorage->Data)
		{
			if (!cam.Primary) continue;

			mainCamera = &cam.Camera;

			auto it = transformStorage->Data.find(entityID);

			if (it != transformStorage->Data.end())
			{
				cameraPosition = it->second.Position;
			}
			break;
		}

		if (!mainCamera) return;

		auto mouseScreenPos = Input::GetMousePosition();
		glm::vec2 screenMousePos = { mouseScreenPos.first, mouseScreenPos.second };

		// Convert screen coordinates to world coordinates
		// Screen: (0,0) top-left, (1280, 720) bottom-right
		// Camera projection: (-10, 10) x (-10, 10)
		// Scale screen coords to camera projection space
		glm::vec2 normalizedMousePos;
		normalizedMousePos.x = (screenMousePos.x / 1280.0f) * 20.0f - 10.0f;
		normalizedMousePos.y = 10.0f - (screenMousePos.y / 720.0f) * 20.0f;

		glm::vec2 worldMousePos = normalizedMousePos + glm::vec2(mainCamera->GetPosition());

		if (Input::IsMouseButtonPressed(MouseCode::Left))
		{
			for (auto entity : GetView<TransformComponent, DragableComponent>())
			{
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& drag = entity.GetComponent<DragableComponent>();

				if (!drag.IsDragging && IsMouseOver(transform, worldMousePos))
				{
					drag.IsDragging = true;
					drag.Offset = { transform.Position.x - worldMousePos.x, transform.Position.y - worldMousePos.y };
					break;
				}
			}
		}

		for (auto entity : GetView<TransformComponent, DragableComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& drag = entity.GetComponent<DragableComponent>();

			if (drag.IsDragging)
			{
				transform.Position.x = worldMousePos.x + drag.Offset.x;
				transform.Position.y = worldMousePos.y + drag.Offset.y;
			}
		}

		if (Input::IsMouseButtonReleased(MouseCode::Left))
		{
			for (auto entity : GetView<DragableComponent>())
			{
				entity.GetComponent<DragableComponent>().IsDragging = false;
			}
		}
	}

	void Scene::DestroyEntity(Entity entity)
	{
		
	}

}