#include "enpch.h"
#include "DragSystem.h"
#include "../Scene.h"
#include "../../Engine/Core/Application.h"

namespace Engine
{
	bool DragSystem::IsMouseOver(const TransformComponent& transform, glm::vec2 mousePos)
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

	void DragSystem::Update(Scene& scene, float dt)
	{

		// Get the primary cameraw
		Camera* mainCamera = nullptr;
		glm::vec3 cameraPosition{ 0.0f };

		auto cameraStorage = scene.GetStorage<CameraComponent>();
		auto transformStorage = scene.GetStorage<TransformComponent>();

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

		auto& window = Application::Get().GetWindow();
		
		unsigned int width = window.GetWidth();  
		unsigned int height = window.GetHeight();

		glm::vec2 normalizedMousePos;
		normalizedMousePos.x = (screenMousePos.x / width) * 20.0f - 10.0f;
		normalizedMousePos.y = 10.0f - (screenMousePos.y / height) * 20.0f;

		glm::vec2 worldMousePos = normalizedMousePos + glm::vec2(mainCamera->GetPosition());

		if (Input::IsMouseButtonPressed(MouseCode::Left))
		{
			for (auto entity : scene.GetView<TransformComponent, DragableComponent>())
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

		for (auto entity : scene.GetView<TransformComponent, DragableComponent>())
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
			for (auto entity : scene.GetView<DragableComponent>())
			{
				entity.GetComponent<DragableComponent>().IsDragging = false;
			}
		}
	}
}