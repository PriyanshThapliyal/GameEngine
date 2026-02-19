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
		#ifdef _DEBUG
		std::cout << "Delta Time: " << deltaTime << " seconds \n";
		#endif
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