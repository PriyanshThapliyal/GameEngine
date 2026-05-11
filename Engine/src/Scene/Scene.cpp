#include "enpch.h"
#include "Scene.h"

namespace Engine
{
	Entity Scene::CreateEntity(const std::string& name)
	{
		uint32_t id = m_NextEntityID++;

		Entity entity(id, this);

		m_Entities.push_back(entity);

		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);
		return entity;
	}

	void Scene::Init()
	{
		// Camera
		Entity camera = CreateEntity("Camera");
		camera.AddComponent<VelocityComponent>();
		camera.AddComponent<CameraComponent>();
		camera.GetComponent<CameraComponent>().Primary = true;

		// Player
		Entity player = CreateEntity("Player");
		//auto playerTexture = Texture::Texture("Engine/assets/Textures/player.png");
		auto& playerTransform = player.AddComponent<TransformComponent>().Position = { 0.0f, 5.0f, 0.0f };
		auto& playerSprite = player.AddComponent<SpriteRendererComponent>();
		auto& playerVelocity = player.AddComponent<VelocityComponent>();
		auto& playerControl = player.AddComponent<ControlledComponent>();
		auto& playerDrag = player.AddComponent<DragableComponent>();
		auto& playerComp = player.AddComponent<PlayerComponent>();

		// Enemy
		Entity enemy = CreateEntity("Enemy");
		//auto enemyTexture = Texture::Texture("Engine/assets/Textures/enemy.png");
		auto& enemyTransform = enemy.AddComponent<TransformComponent>().Position = { 0.0f, -7.0f, 0.0f };
		auto& enemySprite = enemy.AddComponent<SpriteRendererComponent>().Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		auto& enemyVelocity = enemy.AddComponent<VelocityComponent>().Velocity = { 2.5f, 0.0f };
		auto& enemyComp = enemy.AddComponent<EnemyComponent>();

		// Wall
		Entity wallTop = CreateEntity("Top Wall");
		Entity wallBottom = CreateEntity("Bottom Wall");

		auto& topWall = wallTop.AddComponent<TransformComponent>();
		auto& bottomWall = wallBottom.AddComponent<TransformComponent>();
		
		wallTop.AddComponent<SpriteRendererComponent>().Color = { 1.0f, 1.0f, 0.0f, 1.0f };
		wallBottom.AddComponent<SpriteRendererComponent>().Color = { 0.0f, 1.0f, 0.0f, 1.0f };
		
		topWall.Position = { -10.0f, 9.5f, 0.0f };
		bottomWall.Position = { -10.0f, -10.0f, 0.0f };

		topWall.Scale = { 20.0f, 0.5f, 0.0f };
		bottomWall.Scale = { 20.0f, 0.5f, 0.0f };
	}

	void Scene::OnEditorUpdate(float dt, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		for (auto entity : GetView<TransformComponent, SpriteRendererComponent>())
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
		Renderer2D::EndScene();
	}

	void Scene::OnRuntimeUpdate(float dt)
	{
		UpdateInput(dt);
		UpdateDragging(dt);
		UpdateMovement(dt);
		UpdateEnemy(dt);
		UpdateCollision(dt);
		OnRenderRuntime();

	}

	void Scene::OnRenderRuntime()
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
		Renderer2D::EndScene();
	}

	// Handle player input and update velocity components accordingly
	void Scene::UpdateInput(float dt) 
	{
		InputSystem::Update(*this, dt);
	}
	
	// Simple movement system that updates positions based on velocity
	void Scene::UpdateMovement(float dt)
	{
		MovementSystem::Update(*this, dt);
	}

	// Simple dragging system that allows entities with DragableComponent to be dragged with the mouse
	void Scene::UpdateDragging(float dt)
	{
		DragSystem::Update(*this, dt);
	}

	// Simple AI system that moves enemies towards the player
	void Scene::UpdateEnemy(float dt)
	{
		EnemyAISystem::Update(*this, dt);
	}

	void Scene::UpdateCollision(float dt)
	{
		CollisionSystem::Update(*this, dt);
	}

	void Scene::DestroyEntity(Entity entity)
	{
		if (!HasEntity(entity))
		{
			EN_CORE_ERROR("Attempted to destroy non-existent entity with ID: {0}", entity.GetID());
			return;
		}

		if (m_SelectedEntity == entity)
			m_SelectedEntity = {};

		m_Entities.erase(
			std::remove(m_Entities.begin(), m_Entities.end(), entity),
			m_Entities.end()
		);
		
		// Remove components associated with the entity
		for (auto& [type, store] : m_ComponentStores)
		{
			store->Remove(entity);
		}
	}

	void Scene::Clear()
	{
		m_Entities.clear();
		m_ComponentStores.clear();
	}

	const std::vector<Entity>& Scene::GetAllEntities() const
	{
		return m_Entities;
	}

}