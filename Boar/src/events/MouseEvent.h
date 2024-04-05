#pragma once

#include "events/Event.h"
#include "MouseKeys.h"

namespace Warreign
{
	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(const MouseButton button)
			: m_button(button)
		{
		}

		MouseButton getButton() const
		{
			return m_button;
		}

	private:
		MouseButton m_button;
	};

	class MousePressEvent : public MouseButtonEvent
	{
	public:
		MousePressEvent(const MouseButton button)
			: MouseButtonEvent(button)
		{
		}

		EVENT_TYPE(MousePress)
	};

	class MouseReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseReleaseEvent(const MouseButton button)
			: MouseButtonEvent(button)
		{
		}

		EVENT_TYPE(MouseRelease)
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const float xOffset, const float yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset)
		{
		}

		float getXOffset() const
		{
			return m_xOffset;
		}

		float getYOffset() const
		{
			return m_yOffset;
		}

	private:
		const float m_xOffset;
		const float m_yOffset;
	
		EVENT_TYPE(MouseScroll)
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const float x, const float y)
			: m_x(x), m_y(y)
		{
		}

		float getX() const 
		{
			return m_x;
		}

		float getY() const 
		{
			return m_y;
		}

	private:
		const float m_x, m_y;

		EVENT_TYPE(MouseMove)
	};
}