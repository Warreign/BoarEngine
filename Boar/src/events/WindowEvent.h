#pragma once

#include "Event.h"

namespace Warreign
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int newWidth, int newHeight)
			: m_newWidth(newWidth), m_newHeight(newHeight)
		{
		}

		int getWidth() const
		{
			return m_newWidth;
		}

		int getHeight() const
		{
			return m_newHeight;
		}

		EVENT_TYPE(WindowResize)
	private:
		const int m_newWidth;
		const int m_newHeight;
	};
}