#include "enpch.h"
#include "CollisionSystem.h"
#include "../Scene.h"

namespace Engine
{
	void CollisionSystem::Update(Scene& scene, float deltaTime)
	{
		Entity playerEntity;
		Entity enemyEntity;

		//Finding Player
		for (auto entity : scene.GetView<TransformComponent, PlayerComponent>())
		{
			playerEntity = entity;
			break;
		}

		//Finding Enemy
		for (auto entity : scene.GetView<TransformComponent, EnemyComponent>())
		{
			enemyEntity = entity;
			break;
		}

		if (!playerEntity || !enemyEntity)
			return;

		auto& playerTransform = playerEntity.GetComponent<TransformComponent>();
		auto& enemyTransform = enemyEntity.GetComponent<TransformComponent>();

		// Simple AABB collision detection
		bool overlap = 
			abs(playerTransform.Position.x - enemyTransform.Position.x) < (playerTransform.Scale.x + enemyTransform.Scale.x) * 0.5f &&
			abs(playerTransform.Position.y - enemyTransform.Position.y) < (playerTransform	.Scale.y + enemyTransform.Scale.y) * 0.5f;
		
		if (overlap)
		{
			// Collision response: reset player position and stop enemy movement
			playerTransform.Position = { 0.0f, 5.0f, 0.0f };
			if (enemyEntity.HasComponent<VelocityComponent>())
			{
				auto& enemyVelocity = enemyEntity.GetComponent<VelocityComponent>();
				enemyVelocity.Velocity = { 0.0f, 0.0f };
			}
		}
	}
}