#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "RenderCommand.h"
#include "Renderer.h"
#include <memory>
#include "../Engine/Core/Log.h"

namespace Engine
{
	class Renderer2D
	{
	public:
		static void Init();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void SetCamera(const Camera& camera);
		static void BeginScene();
		static void EndScene();
		static void Flush();
	
	private:
		static std::shared_ptr<Shader> s_Shader;
		static glm::mat4 s_ViewProjectionMatrix;
	};

}
