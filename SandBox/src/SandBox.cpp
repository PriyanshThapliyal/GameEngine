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
		if (e.GetEventType() == Engine::EventType::KeyPressed)
		{
			auto& keyEvent = static_cast<Engine::KeyPressedEvent&>(e);

			EN_CORE_TRACE("Key Pressed : {0}  , Repeat : {1} ", (int)keyEvent.GetKeyCode(), keyEvent.IsRepeat());
		}
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}