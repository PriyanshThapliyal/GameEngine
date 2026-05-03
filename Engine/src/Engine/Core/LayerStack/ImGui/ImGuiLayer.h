#pragma once

#include "../Layer.h"

namespace Engine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGuiLayer")
			:Layer(name) {}

		virtual ~ImGuiLayer() = default;

		virtual void Begin() = 0;
		virtual void End() = 0;
	};
}