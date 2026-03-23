#pragma once

#include "RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public Engine::RendererAPI
	{
	public:
		void Init() override;
		void SetClearColor(float r, float g, float b, float a) override;
		void Clear() override;
		void Draw(unsigned int count) override;
		void DrawIndexed(unsigned int count) override;
	};
}

