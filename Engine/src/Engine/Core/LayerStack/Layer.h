#pragma once

#include "Engine/Events/Event.h"
#include <string>

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			:m_DebugName(name) {}

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnRender() {}
		virtual void OnUpdate(float deltaTime) {}

		virtual void OnImGuiRender() {}

	protected:
		std::string m_DebugName;
	};
}
