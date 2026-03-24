#include "enpch.h"
#include "VertexArray.h"

#include "../Engine/Core/Log.h"

#include "RendererAPI.h"
#include "../Platform/OpenGL/OpenGLBuffer.h" //need for specific implementation

#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			EN_CORE_INFO("RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		EN_CORE_INFO("Unknown RendererAPI!");
		return nullptr;
	}
}
