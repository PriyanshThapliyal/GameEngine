#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexArray.h"

#include "Shader.h"
#include "Camera.h"

namespace Engine
{
	class Renderer
	{
	public:
		static void Init();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void SetCamera(const Camera& camera);
	private:
		static std::shared_ptr<VertexArray> s_QuadVA;
		static std::shared_ptr<Shader> s_Shader;
		std::shared_ptr<Engine::VertexBuffer> vb;
		static Camera m_Camera;
		static glm::mat4 s_ViewProjectionMatrix;
	};
}


