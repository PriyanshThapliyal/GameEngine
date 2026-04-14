#include "enpch.h"
#include "Scene.h"
#include "Entity.h"
#include "../Renderer/Renderer2D.h"

namespace Engine
{
	Entity Scene::CreateEntity()
	{
		static uint32_t s_NextID = 1;

		Entity entity(s_NextID++, this);
		m_Entities.push_back(entity);

		m_RenderData[entity.GetID()] = {
			{0.0f, 0.0f},		//Position
			{1.0f, 1.0f},			//Size
			{1.0f, 1.0f, 1.0f, 1.0f}//Color
		};

		return entity;
	}

	void Scene::OnUpdate(float dt)
	{

	}

	void Scene::OnRender()
	{
		Renderer2D::BeginScene(m_Camera);

		for (auto& entity : m_Entities)
		{
			auto& data = m_RenderData[entity.GetID()];

			Renderer2D::DrawQuad(
				data.Position,
				data.Size,
				data.Color
			);
		}
		
		Renderer2D::EndScene();
	}
	void Scene::DestroyEntity(Entity entity)
	{
		
	}
}