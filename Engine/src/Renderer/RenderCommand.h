#pragma once

#include "RendererAPI.h"



namespace Engine
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void SetClearColor(float r, float g, float b, float a)
		{
			s_RendererAPI->SetClearColor(r, g, b, a);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void Draw(unsigned int count)
		{
			s_RendererAPI->Draw(count);
		}

		static void DrawIndexed(unsigned int count)
		{
			s_RendererAPI->DrawIndexed(count);
		}

		static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewPort(x, y, width, height);
		}

	private:
		static Engine::RendererAPI* s_RendererAPI;
	};
}
