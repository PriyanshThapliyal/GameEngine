#include "enpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "../Engine/Core/Log.h"

namespace Engine
{
	void Renderer::Init()
	{
		RenderCommand::Init();
		s_QuadVA.reset(VertexArray::Create());
	}

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size)
	{
		if (!s_QuadVA)
		{
			EN_CORE_ERROR("Renderer::DrawQuad failed! Quad Vertex Array not initialized.");
			return;
		}
		RenderCommand::DrawIndexed(s_QuadVA);
	}
}