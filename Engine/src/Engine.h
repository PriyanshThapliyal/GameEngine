#pragma once
  
// For use by Engine applications

#include "Engine/Core/Core.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Log.h"

#include "Renderer/Shader.h"

#include "Engine/Input/Input.h"
#include "Engine/Input/KeyCode.h"
#include "Engine/Input/MouseCode.h"

#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

#include "Engine/Core/LayerStack.h"

// --- Entry Point ---
#include "Engine/Core/EntryPoint.h"

// Forward declaration of the application creation function so user projects
// can implement Engine::CreateApplication() in their own module.
namespace Engine {
	Application* CreateApplication();
}