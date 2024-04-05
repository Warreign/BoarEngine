#pragma once

#include "Event.h"
#include "KeyboardButton.h"

namespace Warreign
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(const KeyboardButton key)
			: m_key(key)
		{
		}

		KeyboardButton getKey() const
		{
			return m_key;
		}

	private:
		const KeyboardButton m_key;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(const KeyboardButton key)
			: KeyEvent(key)
		{
		}

		EVENT_TYPE(KeyPress)
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(const KeyboardButton key)
			: KeyEvent(key)
		{
		}

		EVENT_TYPE(KeyRelease)
	};
}