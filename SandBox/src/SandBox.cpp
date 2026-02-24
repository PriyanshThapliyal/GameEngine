#include "Engine.h"
#include <iostream>

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
		EN_CORE_TRACE("Delta Time -> {0} ", deltaTime);
		
		if (Engine::Input::IsKeyPressed(Engine::Key::W))
		{
			EN_CORE_INFO("W key pressed");
		}
		// Update game logic here
	}
	virtual void OnRender() override
	{
		// Render game objects here
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}