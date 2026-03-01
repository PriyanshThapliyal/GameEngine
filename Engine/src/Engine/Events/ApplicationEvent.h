#pragma once
#include "Event.h"

namespace Engine {
	
	class WindowCloseEvent final : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType()
		{
			return EventType::WindowClose;
		}

		EventType GetEventType() const override
		{
			return GetStaticType();
		}

		const char* GetName() const override
		{
			return "WindowClose";
		}
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height){}

		EventType GetEventType() const override { return EventType::WindowResize; }
		const char* GetName() const override { return "WindowResize"; }

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

	private:
		unsigned int m_Width, m_Height;
	};
}