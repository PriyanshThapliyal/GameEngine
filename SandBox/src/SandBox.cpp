#include "Engine.h"
#include "enpch.h"
#include "../SandboxLayer.h" 
#include <glad/glad.h>

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

private:
	
protected:
	virtual void OnUpdate(float deltaTime) override
	{
		// Update game logic here using deltaTime for frame-independent movement
	}
	virtual void OnRender() override
	{

	}

};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}