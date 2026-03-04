#pragma once
#include "Event.h"
#include "Engine/Input/KeyCode.h"

namespace Engine
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode , bool isRepeat)
			: KeyEvent(keycode) , m_IsRepeat(isRepeat) {}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }

		const char* GetName() const override { return "KeyPressed"; }

		bool IsRepeat() const { return m_IsRepeat; }

	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }

		const char* GetName() const override { return "KeyReleased"; }
	};
}