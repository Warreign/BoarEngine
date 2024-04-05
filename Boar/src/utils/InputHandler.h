#pragma once

#include "events/Event.h"

namespace Warreign
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

	private:
		void OnKeyPress();

	public:
		void OnEvent(const Event& e);

	};
}