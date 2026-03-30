#include "enpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLRendererAPI.h"

namespace Engine
{
	void OpenGLRendererAPI::Init() 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::Draw(unsigned int count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

	void OpenGLRendererAPI::DrawIndexed(std::shared_ptr<VertexArray> vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, 
					   vertexArray->GetIndexBuffer()->GetCount(), 
					   GL_UNSIGNED_INT, 
					   nullptr);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}
}