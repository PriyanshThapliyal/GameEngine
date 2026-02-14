#pragma once

#ifdef EN_PLATFORM_WINDOWS

namespace Engine {
	Application* CreateApplication();
}

int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;

}


#endif