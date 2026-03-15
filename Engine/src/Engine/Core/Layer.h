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

	protected:
		std::string m_DebugName;
	};
}
