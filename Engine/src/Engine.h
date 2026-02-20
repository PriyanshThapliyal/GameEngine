#pragma once
  
// For use by Engine applications

#include "Engine/Core.h"
#include "Engine/Application.h"
#include "Engine/EntryPoint.h"
#include "Engine/Input.h"
#include "Platform/Window/KeyCode.h"

// Forward declaration of the application creation function so user projects
// can implement Engine::CreateApplication() in their own module.
namespace Engine {
	Application* CreateApplication();
}