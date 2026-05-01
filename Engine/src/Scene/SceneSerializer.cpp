#include "enpch.h"

#include "SceneSerializer.h"
#include "json.hpp"
#include <fstream>

#include "Scene.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteRendererComponent.h"

using json = ::nlohmann::json;

namespace Engine
{
	SceneSerializer::SceneSerializer(Scene* scene)
		: m_Scene(scene)
	{}

	SceneSerializer::~SceneSerializer()
	{}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		json sceneJson;
		sceneJson["Entities"] = json::array();

		auto entities = m_Scene->GetView<>();
		EN_CORE_INFO("Serializing {0} entities", entities.size());

		for (auto entity : entities)
		{
			json entityJson;

			// Transform components to JSON
			if (entity.HasComponent<TransformComponent>())
			{
				auto& tc = entity.GetComponent<TransformComponent>();

				entityJson["Transform"] = {
					{"Position", {tc.Position.x, tc.Position.y, tc.Position.z}},
					{"Scale", {tc.Scale.x, tc.Scale.y, tc.Scale.z}},
					{"Rotation", tc.Rotation}
				};
			}

			// Sprite components to JSON
			if (entity.HasComponent<SpriteRendererComponent>())
			{
				auto& sc = entity.GetComponent<SpriteRendererComponent>();
				entityJson["Sprite"] = {
					{"Color", {sc.Color.r, sc.Color.g, sc.Color.b, sc.Color.a}}
				};
			}

			// Velocity components to JSON
			if (entity.HasComponent<VelocityComponent>())
			{
				auto& vc = entity.GetComponent<VelocityComponent>();

				entityJson["Velocity"] = {
					{"Velocity", {vc.Velocity.x, vc.Velocity.y}},
					{"Speed", vc.Speed}
				};
			}

			// Controlled components to JSON
			if (entity.HasComponent<ControlledComponent>())
			{
				auto& cc = entity.GetComponent<ControlledComponent>();

				entityJson["Controlled"] = {
					{"IsControlled", cc.IsControlled}
				};
			}

			// Camera components to JSON
			if (entity.HasComponent<CameraComponent>())
			{
				auto& cc = entity.GetComponent<CameraComponent>();

				entityJson["Camera"] = {
					{"Primary", cc.Primary},
					{"Zoom", {cc.Camera.GetPosition().x, cc.Camera.GetPosition().y, cc.Camera.GetPosition().z}}
				};
			}

			// Enemy components to JSON
			if (entity.HasComponent<EnemyComponent>())
			{
				auto& ec = entity.GetComponent<EnemyComponent>();
				entityJson["Enemy"] = {
					{"Speed", ec.Speed},
					{"Time", ec.Time}
				};
			}

			// Player components to JSON
			if (entity.HasComponent<PlayerComponent>())
			{
				auto& pc = entity.GetComponent<PlayerComponent>();
				entityJson["Player"] = {
					{"Speed", pc.Speed}
				};
			}

			if (entity.HasComponent<DragableComponent>())
			{
				auto& dc = entity.GetComponent<DragableComponent>();
				entityJson["Dragable"] = {
					{"IsDragging", dc.IsDragging},
					{"Offset", {dc.Offset.x, dc.Offset.y}}
				};
			}


			sceneJson["Entities"].push_back(entityJson);
		}

		std::ofstream file(filepath);
		if (!file.is_open())
		{
			EN_CORE_ERROR("Failed to open file for serialization: {0}", filepath);
			return;
		}

		file << sceneJson.dump(4);
		file.close();

		EN_CORE_INFO("Scene saved successfully to {0}", filepath);
	}

	void SceneSerializer::Deserialize(const std::string& filepath)
	{
		EN_CORE_INFO("Loading Scene from {0}", filepath);

		std::ifstream file(filepath);
		if (!file.is_open())
		{
			EN_CORE_ERROR("Failed to open file for deserialization: {0}", filepath);
			return;
		}

		json sceneJson;
		try
		{
			file >> sceneJson;
		}
		catch (const std::exception& e)
		{
			EN_CORE_ERROR("Failed to parse JSON: {0}", e.what());
			return;
		}

		if (!sceneJson.contains("Entities") || !sceneJson["Entities"].is_array())
		{
			EN_CORE_ERROR("Invalid scene file format: {0}", filepath);
			return;
		}

		EN_CORE_INFO("Deserializing {0} entities", sceneJson["Entities"].size());

		for (const auto& entityJson : sceneJson["Entities"])
		{
			Entity entity = m_Scene->CreateEntity();
			EN_CORE_INFO("Created entity with ID: {0}", entity.GetID());

			// Deserialize Transform component (already created by CreateEntity, just get and modify)
			if (entityJson.contains("Transform"))
			{
				const auto& transformJson = entityJson["Transform"];
				auto& tc = entity.GetComponent<TransformComponent>();

				if (transformJson.contains("Position") && transformJson["Position"].is_array())
				{
					const auto& pos = transformJson["Position"];
					tc.Position = { pos[0], pos[1], pos[2] };
				}

				if (transformJson.contains("Scale") && transformJson["Scale"].is_array())
				{
					const auto& scale = transformJson["Scale"];
					tc.Scale = { scale[0], scale[1], scale[2] };
				}

				if (transformJson.contains("Rotation"))
				{
					tc.Rotation = transformJson["Rotation"].get<float>();
				}
			}

			// Deserialize Sprite component
			if (entityJson.contains("Sprite"))
			{
				const auto& spriteJson = entityJson["Sprite"];
				auto& sc = entity.AddComponent<SpriteRendererComponent>();

				if (spriteJson.contains("Color") && spriteJson["Color"].is_array())
				{
					const auto& color = spriteJson["Color"];
					sc.Color = { color[0], color[1], color[2], color[3] };
				}
			}

			// Deserialize Velocity component
			if (entityJson.contains("Velocity"))
			{
				const auto& velocityJson = entityJson["Velocity"];
				auto& vc = entity.AddComponent<VelocityComponent>();

				if(velocityJson.contains("Velocity") && velocityJson["Velocity"].is_array())
				{
					const auto& vel = velocityJson["Velocity"];
					vc.Velocity = { vel[0], vel[1] };
				}
				if (velocityJson.contains("Speed"))
				{
					vc.Speed = velocityJson["Speed"].get<float>();
				}
			}

			// Deserialize Controlled component
			if (entityJson.contains("Controlled"))
			{
				const auto& controlledJson = entityJson["Controlled"];
				auto& cc = entity.AddComponent<ControlledComponent>();

				if (controlledJson.contains("IsControlled"))
				{
					cc.IsControlled = controlledJson["IsControlled"].get<bool>();
				}
			}

			// Deserialize Camera component
			if (entityJson.contains("Camera"))
			{
				const auto& cameraJson = entityJson["Camera"];
				auto& cc = entity.AddComponent<CameraComponent>();
				if (cameraJson.contains("Primary"))
				{
					cc.Primary = cameraJson["Primary"].get<bool>();
				}
				if (cameraJson.contains("Zoom") && cameraJson["Zoom"].is_array())
				{
					const auto& zoom = cameraJson["Zoom"];
					cc.Camera.SetPosition({ zoom[0], zoom[1], zoom[2] });
				}
			}

			// Deserialize Enemy component
			if (entityJson.contains("Enemy"))
			{
				const auto& enemyJson = entityJson["Enemy"];
				auto& ec = entity.AddComponent<EnemyComponent>();
				if (enemyJson.contains("Speed"))
				{
					ec.Speed = enemyJson["Speed"].get<float>();
				}
				if (enemyJson.contains("Time"))
				{
					ec.Time = enemyJson["Time"].get<float>();
				}
			}

			// Deserialize Player component
			if (entityJson.contains("Player"))
			{
				const auto& playerJson = entityJson["Player"];
				auto& pc = entity.AddComponent<PlayerComponent>();
				if (playerJson.contains("Speed"))
				{
					pc.Speed = playerJson["Speed"].get<float>();
				}
			}

			// Deserialize Dragable component
			if (entityJson.contains("Dragable"))
			{
				const auto& dragableJson = entityJson["Dragable"];
				auto& dc = entity.AddComponent<DragableComponent>();
				if (dragableJson.contains("IsDragging"))
				{
					dc.IsDragging = dragableJson["IsDragging"].get<bool>();
				}
				if (dragableJson.contains("Offset") && dragableJson["Offset"].is_array())
				{
					const auto& offset = dragableJson["Offset"];
					dc.Offset = { offset[0], offset[1] };
				}
			}
		}

		EN_CORE_INFO("Scene loaded successfully");
	}

}