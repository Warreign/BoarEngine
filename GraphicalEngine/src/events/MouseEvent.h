#pragma once

#include "events/Event.h"

namespace Warreign
{
	//class MouseEvent() : public

	class MousePressEvent : public Event
	{
	public:
		MousePressEvent() = default;

		EVENT_TYPE(MousePress)
	};

	class MouseReleaseEvent : public Event
	{
	public:
		MouseReleaseEvent() = default;

		EVENT_TYPE(MouseRelease)
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent() = default;

		EVENT_TYPE(MouseScroll)
	};
}