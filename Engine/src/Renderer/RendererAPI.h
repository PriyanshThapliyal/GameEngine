#pragma once

#include <cstdint>
#include "VertexArray.h"

namespace Engine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL,
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void Clear() = 0;
		
		virtual void Draw(unsigned int count) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray) = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	
		// Static API selection
		static API GetAPI() { return s_API; }
	
	private:
		static API s_API;
	};

}

