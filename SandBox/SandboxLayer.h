#pragma once

#include "Engine/Layer.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Log.h"

class SandboxLayer : public Engine::Layer
{
public:
	SandboxLayer()
		: Layer("SandboxLayer") {
	}

	void OnAttach() override
	{
		EN_CORE_WARN("SandboxLayer Attached");
	}

	void OnEvent(Engine::Event& e) override
	{
		if (e.GetEventType() == Engine::EventType::KeyPressed)
		{
			auto& keyEvent = static_cast<Engine::KeyPressedEvent&>(e);

			EN_CORE_TRACE("Key Pressed : {0} , Repeat : {1}", (int)keyEvent.GetKeyCode(), keyEvent.IsRepeat());
		}

		//if (e.GetEventType() == Engine::EventType::MouseMoved)
		//{
		//	auto& mouseEvent = static_cast<Engine::MouseMovedEvent&>(e);

		//	EN_CORE_TRACE("Mouse Moved : {0} , {1}", mouseEvent.GetX(), mouseEvent.GetY());
		//}

		if (e.GetEventType() == Engine::EventType::MouseButtonPressed)
		{
			auto& mouseEvent = static_cast<Engine::MouseButtonPressedEvent&>(e);

			EN_CORE_TRACE("Mouse Button Pressed : {0}", mouseEvent.GetMouseButton());
		}

		if (e.GetEventType() == Engine::EventType::MouseScrolled)
		{
			auto& mouseEvent = static_cast<Engine::MouseScrolledEvent&>(e);

			EN_CORE_TRACE("Mouse Scrolled : {0} , {1}", mouseEvent.GetXOffset(), mouseEvent.GetYOffset());
		}
	}
};