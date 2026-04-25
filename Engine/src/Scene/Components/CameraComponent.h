#pragma once

#include "../../Renderer/Camera.h"

namespace Engine
{
	struct CameraComponent
	{
		CameraComponent()
			: Camera(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f)
		{}

		Camera Camera;
		bool Primary = true; // Main camera for rendering
	};
}