#include "enpch.h"
#include "Renderer2D.h"

struct QuadVertex
{
	glm::vec3 Position;
	glm::vec4 Color;
};

struct Renderer2DData
{
	static const uint32_t MaxQuads = 10000;
	static const uint32_t MaxVertices = MaxQuads * 4;
	static const uint32_t MaxIndices = MaxQuads * 6;
	std::shared_ptr<Engine::VertexBuffer> VertexBuffer;
	std::shared_ptr<Engine::VertexArray> VertexArray;
	QuadVertex* BufferBase = nullptr;
	QuadVertex* BufferPtr = nullptr;
	uint32_t QuadCount = 0;
};

namespace Engine
{
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Shader = std::make_shared<Shader>("Engine/assets/Shaders/quad.vert", "Engine/assets/Shaders/quad.frag");

		s_Data.VertexArray = VertexArray::Create();

		s_Data.VertexBuffer = VertexBuffer::Create(
			nullptr, Renderer2DData::MaxVertices * sizeof(QuadVertex)
		);

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position", false},
			{ ShaderDataType::Float4 , "a_Color", false}
		};

		s_Data.BufferBase = new QuadVertex[Renderer2DData::MaxVertices];

		if (!s_Data.BufferBase)
		{
			EN_CORE_ERROR("BufferBase NOT initialized!");
			return;
		}

		s_Data.VertexBuffer->SetLayout(layout);
		s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer);

		// Create Index buffer

		uint32_t* indices = new uint32_t[Renderer2DData::MaxIndices];

		uint32_t offset = 0;

		for (uint32_t i = 0; i < Renderer2DData::MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			
			offset += 4;
		}

		auto indexBuffer = IndexBuffer::Create(indices, Renderer2DData::MaxIndices);
		s_Data.VertexArray->SetIndexBuffer(std::shared_ptr<IndexBuffer>(indexBuffer));
	
		delete[] indices;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		if (!s_Data.BufferPtr)
		{
			EN_CORE_ERROR("BufferpPtr is NULL!");
			return;
		}

		if (s_Data.QuadCount >= Renderer2DData::MaxQuads)
		{
			Flush();
			s_Data.BufferPtr = s_Data.BufferBase;
			s_Data.QuadCount = 0;
			EN_CORE_INFO("Max quad count reached, flushing data!");
		}

		glm::vec3 p0 = { position.x, position.y, 0.0f };
		glm::vec3 p1 = { position.x + size.x, position.y, 0.0f };
		glm::vec3 p2 = { position.x + size.x, position.y + size.y, 0.0f };
		glm::vec3 p3 = { position.x, position.y + size.y, 0.0f };

		//Vertex 1
		s_Data.BufferPtr->Position = p0;
		s_Data.BufferPtr->Color = color;
		s_Data.BufferPtr++;
	
		//Vertex 2
		s_Data.BufferPtr->Position = p1;
		s_Data.BufferPtr->Color = color;
		s_Data.BufferPtr++;

		//Vertex 3
		s_Data.BufferPtr->Position = p2;
		s_Data.BufferPtr->Color = color;
		s_Data.BufferPtr++;

		//Vertex 4
		s_Data.BufferPtr->Position = p3;
		s_Data.BufferPtr->Color = color;
		s_Data.BufferPtr++;

		s_Data.QuadCount++;
	}

	void Renderer2D::SetCamera(const Camera& camera)
	{
		s_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}


	void Renderer2D::BeginScene()
	{
		s_Data.BufferPtr = s_Data.BufferBase;
		s_Data.QuadCount = 0;
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{	
		if (!s_Data.VertexBuffer) EN_CORE_ERROR("VB NULL");
		if (!s_Data.VertexArray) EN_CORE_ERROR("VA NULL");
		if (!s_Shader) EN_CORE_ERROR("Shader NULL");

		uint32_t size = (uint32_t)((uint8_t*)s_Data.BufferPtr - (uint8_t*)s_Data.BufferBase);

		s_Data.VertexBuffer->Bind();
		s_Data.VertexBuffer->SetData(s_Data.BufferBase, size);
		
		s_Shader->Bind();
		s_Shader->SetUniformMat4("u_ViewProjection", s_ViewProjectionMatrix);

		s_Data.VertexArray->Bind();

		RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.QuadCount * 6);
	}

	std::shared_ptr<Shader> Renderer2D::s_Shader = nullptr;
	glm::mat4 Renderer2D::s_ViewProjectionMatrix = glm::mat4(1.0f);
}