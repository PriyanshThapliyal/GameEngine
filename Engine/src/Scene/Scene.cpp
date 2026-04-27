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
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"

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
		// Camera
		Entity camera = CreateEntity();
		camera.AddComponent<VelocityComponent>();
		camera.AddComponent<CameraComponent>();
		camera.GetComponent<CameraComponent>().Primary = true;

		// Player
		auto playerTexture = Texture::Texture("Engine/assets/Textures/player.png");
		Entity player = CreateEntity();
		auto& playerTransform = player.AddComponent<TransformComponent>().Position = { 0.0f, 5.0f, 0.0f };
		auto& playerSprite = player.AddComponent<SpriteRendererComponent>();
		auto& playerVelocity = player.AddComponent<VelocityComponent>();
		auto& playerControl = player.AddComponent<ControlledComponent>();
		auto& playerDrag = player.AddComponent<DragableComponent>();
		auto& playerComp = player.AddComponent<PlayerComponent>();

		// Enemy
		auto enemyTexture = Texture::Texture("Engine/assets/Textures/enemy.png");
		Entity enemy = CreateEntity();
		auto& enemyTransform = enemy.AddComponent<TransformComponent>().Position = { 0.0f, -7.0f, 0.0f };
		auto& enemySprite = enemy.AddComponent<SpriteRendererComponent>().Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		auto& enemyVelocity = enemy.AddComponent<VelocityComponent>().Velocity = { 2.5f, 0.0f };
		auto& enemyComp = enemy.AddComponent<EnemyComponent>();

		// Wall
		Entity wallTop = CreateEntity();
		Entity wallBottom = CreateEntity();

		auto& topWall = wallTop.AddComponent<TransformComponent>();
		auto& bottomWall = wallBottom.AddComponent<TransformComponent>();
		
		wallTop.AddComponent<SpriteRendererComponent>().Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		wallBottom.AddComponent<SpriteRendererComponent>().Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		
		topWall.Position = { -10.0f, 9.5f, 0.0f };
		bottomWall.Position = { -10.0f, -10.0f, 0.0f };

		topWall.Scale = { 20.0f, 0.5f, 0.0f };
		bottomWall.Scale = { 20.0f, 0.5f, 0.0f };
	}

	void Scene::OnUpdate(float dt)
	{
		Scene::UpdateInput(dt);
		Scene::UpdateDragging(dt);
		Scene::UpdateMovement(dt);
		Scene::UpdateEnemy(dt);

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
			
			if (sprite.Texture)
			{
				Renderer2D::DrawQuad(
					transform.Position,
					transform.Scale,
					*sprite.Texture,
					sprite.Color
				);
			}
			else
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
			auto& transform = entity.GetComponent<TransformComponent>();

			velocity.Velocity = { 0.0f, 0.0f };

			if (Input::IsKeyPressed(KeyCode::D)) velocity.Velocity.x += 1.0f;
			if (Input::IsKeyPressed(KeyCode::A)) velocity.Velocity.x -= 1.0f;
			if (Input::IsKeyPressed(KeyCode::W)) velocity.Velocity.y += 1.0f;
			if (Input::IsKeyPressed(KeyCode::S)) velocity.Velocity.y -= 1.0f;

			if (transform.Position.x > 9.0f )
			{
				transform.Position.x = 9.0f;
				velocity.Velocity.x = 0.0f;
			}
			
			if (transform.Position.x < -10.0f)
			{
				transform.Position.x = -10.0f;
				velocity.Velocity.x = 0.0f;
			}

			if (transform.Position.y > 8.5f)
			{
				transform.Position.y = 8.0f;
				velocity.Velocity.y = 0.0f;
			}
			
			if (transform.Position.y < -9.5f)
			{
				transform.Position.y = -9.0f;
				velocity.Velocity.y = 0.0f;
			}
			
			velocity.Speed = 5.0f;

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

	void Scene::UpdateEnemy(float dt)
	{
		glm::vec3 playerPos{ 0.0f };
		bool foundPlayer = false;

		for (auto entity : GetView<TransformComponent, PlayerComponent>())
		{
			playerPos = entity.GetComponent<TransformComponent>().Position;
			foundPlayer = true;
			break; // Assuming only one player, we can break after finding it
		}
		
		if (!foundPlayer) return;

		//  Enemy Movement Logic

		for (auto entity : GetView<TransformComponent, EnemyComponent, VelocityComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& velocity = entity.GetComponent<VelocityComponent>();

			glm::vec3 direction = playerPos - transform.Position;

			if (glm::length(direction) > 0.001f)
			{
				direction = glm::normalize(direction);
				velocity.Velocity = glm::vec2(direction) * velocity.Speed;
			}
			else
			{
				velocity.Velocity = { 0.0f, 0.0f };
			}
		}
	}

	void Scene::DestroyEntity(Entity entity)
	{
		
	}
}