#include "Engine.h"
#include "enpch.h"
#include "../SandboxLayer.h" 

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
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

};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}