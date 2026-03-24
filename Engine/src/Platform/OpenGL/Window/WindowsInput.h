#pragma once

#include "Engine/Input/Input.h"

namespace Engine{

	class WindowsInput : public Input
	{
	public:
		
		
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}