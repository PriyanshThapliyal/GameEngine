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
		//EN_CORE_TRACE("Delta Time -> {0} ", deltaTime);

		if (Engine::Input::IsKeyPressed(Engine::KeyCode::W))
		{
			EN_CORE_INFO("W key pressed");
		}

		if (Engine::Input::IsMouseButtonPressed(Engine::MouseCode::Left))
		{
			EN_CORE_INFO("Left mouse button pressed");
		}

		//EN_CORE_TRACE("Mouse Position -> {0} , {1} ", Engine::Input::GetMousePosition().first, Engine::Input::GetMousePosition().second);
		
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