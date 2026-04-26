#pragma once
#include "KeyCode.h"
#include "MouseCode.h"

#include<Engine/Core/Core.h>

namespace Engine
{
	class ENGINE_API Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static bool IsKeyReleased(KeyCode key) { return s_Instance->IsKeyReleasedImpl(key); }
		inline static bool IsMouseButtonReleased(MouseCode button) { return s_Instance->IsMouseButtonReleasedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsKeyReleasedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual bool IsMouseButtonReleasedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

	private:
		static Input* s_Instance ;
	};
}