#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void Init();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size);
	
	private:
		static std::shared_ptr<VertexArray> s_QuadVA;
	};
}


