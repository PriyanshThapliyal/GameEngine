#include "enpch.h"
#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}