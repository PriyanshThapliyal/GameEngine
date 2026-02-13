#pragma once
  
// For use by Engine applications

#include "Engine/Core.h"
#include "Engine/Application.h"
#include "Engine/EntryPoint.h"

// Forward declaration of the application creation function so user projects
// can implement Engine::CreateApplication() in their own module.
namespace Engine {
	Application* CreateApplication();
}