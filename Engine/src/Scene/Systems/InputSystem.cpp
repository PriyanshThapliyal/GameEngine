#include "enpch.h"
#include "InputSystem.h"
#include "../Scene.h"

namespace Engine
{
	void InputSystem::Update(Scene& scene, float dt)
	{

		// Handle camera input (only the primary camera should respond)
		for (auto entity : scene.GetView<ControlledComponent, VelocityComponent, CameraComponent, PlayerComponent>())
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
		for (auto entity : scene.GetView<ControlledComponent, VelocityComponent, PlayerComponent>())
		{
			auto& control = entity.GetComponent<ControlledComponent>();
			if (!control.IsControlled) continue;

			// Skip if this entity has a camera (already handled above)
			if (entity.HasComponent<CameraComponent>()) continue;

			auto& velocity = entity.GetComponent<VelocityComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& playerComp = entity.GetComponent<PlayerComponent>();

			velocity.Velocity = { 0.0f, 0.0f };

			if (Input::IsKeyPressed(KeyCode::D)) velocity.Velocity.x += 1.0f;
			if (Input::IsKeyPressed(KeyCode::A)) velocity.Velocity.x -= 1.0f;
			if (Input::IsKeyPressed(KeyCode::W)) velocity.Velocity.y += 1.0f;
			if (Input::IsKeyPressed(KeyCode::S)) velocity.Velocity.y -= 1.0f;

			if (transform.Position.x > 9.0f)
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
				transform.Position.y = 8.5f;
				velocity.Velocity.y = 0.0f;
			}

			if (transform.Position.y < -9.5f)
			{
				transform.Position.y = -9.5f;
				velocity.Velocity.y = 0.0f;
			}

			if (glm::length(velocity.Velocity) > 0.0f)
				velocity.Velocity = glm::normalize(velocity.Velocity) * playerComp.Speed;
		}
	}
}
