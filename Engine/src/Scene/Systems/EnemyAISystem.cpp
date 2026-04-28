#include "enpch.h"
#include "EnemyAISystem.h"
#include "../Scene.h"

namespace Engine
{
	void EnemyAISystem::Update(Scene& scene, float dt)
	{
		// Get lists from the specific scene instance passed in (avoid calling non-static members without an object)
		auto enemies = scene.GetView<TransformComponent, EnemyComponent, VelocityComponent>();
		auto players = scene.GetView<TransformComponent, PlayerComponent>();

		if (players.empty())
			return;

		// Simple AI: move each enemy towards the first player found
		auto& playerTransform = players[0].GetComponent<TransformComponent>();

		for (auto entity : enemies)
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& enemyComp = entity.GetComponent<EnemyComponent>();
			auto& velocity = entity.GetComponent<VelocityComponent>();

			glm::vec2 toPlayer = glm::vec2(
				playerTransform.Position.x - transform.Position.x,
				playerTransform.Position.y - transform.Position.y
			);

			if (glm::length(toPlayer) > 0.0001f)
				toPlayer = glm::normalize(toPlayer);
			else
				toPlayer = glm::vec2(0.0f);

			velocity.Velocity = toPlayer * enemyComp.Speed;

			enemyComp.Time += dt;
		}
	}
}
