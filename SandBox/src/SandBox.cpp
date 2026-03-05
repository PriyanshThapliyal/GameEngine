#include "Engine.h"
#include "enpch.h"

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

protected:
	virtual void OnUpdate(float deltaTime) override
	{
		// Update game logic here using deltaTime for frame-independent movement
	}
	virtual void OnRender() override
	{
		// Render game objects here
	}

	virtual void OnEvent(Engine::Event& e) override
	{
		Application::OnEvent(e); // Call base class event handling

		if (e.GetEventType() == Engine::EventType::KeyPressed)
		{
			auto& keyEvent = static_cast<Engine::KeyPressedEvent&>(e);

			EN_CORE_TRACE("Key Pressed : {0}  , Repeat : {1} ", (int)keyEvent.GetKeyCode(), keyEvent.IsRepeat());
		}

		if (e.GetEventType() == Engine::EventType::MouseMoved)
		{
			auto& mouseEvent = static_cast<Engine::MouseMovedEvent&>(e);
			EN_CORE_TRACE("Mouse Moved : {0} , {1}", mouseEvent.GetX(), mouseEvent.GetY());
		}

		if (e.GetEventType() == Engine::EventType::MouseButtonPressed)
		{
			auto& mouseEvent = static_cast<Engine::MouseButtonPressedEvent&>(e);
			EN_CORE_TRACE("Mouse Button Pressed : {0} ", mouseEvent.GetMouseButton());
		}
		if (e.GetEventType() == Engine::EventType::MouseScrolled)
		{
			auto& mouseEvent = static_cast<Engine::MouseScrolledEvent&>(e);
			EN_CORE_TRACE("Mouse Scrolled : {0} , {1}", mouseEvent.GetXOffset(), mouseEvent.GetYOffset());
		}
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}