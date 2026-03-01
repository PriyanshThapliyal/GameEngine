#pragma once
#include <functional>

namespace Engine
{

	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize
	};

	class Event
	{
	public :
		virtual ~Event() = default; // Virtual desturctor -> polymorphic base class

		virtual EventType GetEventType() const = 0;  // Pure virtual function -> makes this class abstract
		virtual const char* GetName() const = 0;

		bool Handled = false;

	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T , typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}