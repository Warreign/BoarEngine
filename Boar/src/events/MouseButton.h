#pragma once

#include <cstdint>

namespace Warreign 
{
	using MouseButton = uint8_t;

	namespace Mouse
	{
		enum : MouseButton
		{
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,

			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}

