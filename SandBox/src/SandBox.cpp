#include "Engine.h"

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
	virtual void OnUpdate() override
	{
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