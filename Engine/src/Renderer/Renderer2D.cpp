#include "enpch.h"
#include "Renderer2D.h"

namespace Engine
{
	void Renderer2D::Init()
	{
		Renderer::Init();
		s_Shader = Renderer::GetShader();
		s_VertexArray = Renderer::GetQuadVA();

		if (!s_Shader)
		{
			EN_CORE_ERROR("Renderer2D: Shader not initialized!");
		}

		if (!s_VertexArray)
		{
			EN_CORE_ERROR("Renderer2D: VertexArray not initialized!");
		}

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{

		if (!s_Shader)
		{
			EN_CORE_ERROR("Renderer2D: Shader is NULL. Aborting draw.");
			return;
		}

		// Build the transformation matrix for the quad to be drawn
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x , position.y , 0.0f })
							* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	
		// Bind the shader, set uniforms
		s_Shader->Bind();
		s_Shader->SetUniformMat4("u_Model", transform);
		s_Shader->SetUniformFloat4("u_Color", color.r, color.g, color.b, color.a);
		s_Shader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);

		// Bind VAO
		s_VertexArray->Bind();

		// Draw the quad using the bound shader and vertex array

		RenderCommand::DrawIndexed(s_VertexArray);
	}

	void Renderer2D::SetCamera(const Camera& camera)
	{
		s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	std::shared_ptr<Shader> Renderer2D::s_Shader = nullptr;
	std::shared_ptr<VertexArray> Renderer2D::s_VertexArray = nullptr;
	glm::mat4 Renderer2D::s_ViewProjectionMatrix = glm::mat4(1.0f);
}