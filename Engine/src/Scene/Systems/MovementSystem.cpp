#include "enpch.h"
#include "MovementSystem.h"
#include "../Scene.h"

namespace Engine
{
	void MovementSystem::Update(Scene& scene, float dt)
	{
		for (auto entity : scene.GetView<TransformComponent, VelocityComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& velocity = entity.GetComponent<VelocityComponent>();

			transform.Position += glm::vec3(velocity.Velocity * dt, 0.0f);
		}
	}
}