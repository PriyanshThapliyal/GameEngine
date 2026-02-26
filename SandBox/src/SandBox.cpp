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

		if (Engine::Input::IsKeyPressed(Engine::Key::W))
		{
			EN_CORE_INFO("W key pressed");
		}

		EN_CORE_INFO("Mouse Position -> {0} , {1} ", Engine::Input::GetMousePosition().first, Engine::Input::GetMousePosition().second);
		//EN_CORE_INFO("Mouse Button Pressed -> {0}", Engine::Input::IsMouseButtonPressed(0)); 

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