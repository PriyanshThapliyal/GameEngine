#pragma once
#include "Event.h"

namespace Engine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		
		const char* GetName() const override { return "MouseMoved"; }

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int buttoncode )
			: m_Button(buttoncode)  {
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return GetStaticType(); }

		const char* GetName() const override { return "MouseButtonPressed"; }

		int GetMouseButton() const { return m_Button; }

	private:
		int m_Button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int buttoncode)
			: m_Button(buttoncode) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return GetStaticType(); }

		char const* GetName() const override { return "MouseButtonReleased"; }

		int GetMouseButton() const { return m_Button; }

	private:
		int m_Button;
	};


	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset , float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }

		const char* GetName() const override { return "MouseScrolled"; }

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

	private:
		float m_XOffset, m_YOffset;
	};

};