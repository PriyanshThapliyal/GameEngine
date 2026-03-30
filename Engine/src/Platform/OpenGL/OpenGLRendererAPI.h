#pragma once

#include "../../Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public Engine::RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		void Draw(unsigned int count) override;
		void DrawIndexed(std::shared_ptr<VertexArray> vertexArray) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}

