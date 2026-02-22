#pragma once

#ifdef EN_PLATFORM_WINDOWS

namespace Engine {
	Application* CreateApplication();
}

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EN_CORE_WARN("Initialized Log!");
	EN_INFO("Initialized Log!");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;

}


#endif