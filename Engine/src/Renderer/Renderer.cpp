#include "enpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "../Engine/Core/Log.h"

namespace Engine
{
    void Renderer::Init()
    {
        RenderCommand::Init();

        s_QuadVA = VertexArray::Create();

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        uint32_t indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        auto vb = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
        vb->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
            });
        s_QuadVA->AddVertexBuffer(vb);

        auto ib = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, 6));
        s_QuadVA->SetIndexBuffer(ib);

        s_Shader = std::make_shared<Shader>(
            "Engine/assets/Shaders/quad.vert",
            "Engine/assets/Shaders/quad.frag"
        );

        if (!s_Shader)
        {
            EN_CORE_ERROR("Failed to create shader!");
        }
    }

	void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (!s_QuadVA)
		{
			EN_CORE_ERROR("Renderer::DrawQuad failed! Quad Vertex Array not initialized.");
			return;
		}

		if (!s_Shader)
		{
			EN_CORE_ERROR("Shader is NULL. Aborting draw.");
			return;
		}

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::scale(model, glm::vec3(size, 1.0f));

        s_Shader->Bind();
        s_Shader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);
		s_Shader->SetUniformMat4("u_Model", model);
		s_Shader->SetUniformFloat4("u_Color", color.r, color.g, color.b, color.a);

		s_QuadVA->Bind();
		RenderCommand::DrawIndexed(s_QuadVA, 0);
	}

    void Renderer::SetCamera(const Camera& camera)
    {
		s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	std::shared_ptr<VertexArray> Renderer::s_QuadVA = nullptr;
	std::shared_ptr<Shader> Renderer::s_Shader = nullptr;
	Camera Renderer::m_Camera(-2.0f, 2.0f, -2.0f, 2.0f , -1.0f, 1.0f);
	glm::mat4 Renderer::s_ViewProjectionMatrix = glm::mat4(1.0f);
}