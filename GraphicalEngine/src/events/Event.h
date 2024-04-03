#pragma once

namespace Warreign
{

	class Event
	{
#define EVENT_TYPE(type) virtual Type getType() const { return type; }\
							virtual const char* getName() const { return #type; }\
							static Type getStatictype() { return type; }
	public:
		enum Type
		{
			WindowClose, WindowResize,
			MousePress, MouseRelease, MouseScroll,
			KeyPress, KeyRelease, KeyRepeat
		};

	public:
		//virtual ~Event();

	private:
		bool handled = false;

	public:
		void consume() { handled = true; }

		template<typename T, typename F>
		void handle(const F& func)
		{
			if (getType() == T::getStaticType())
			{
				func(static_cast<T&>(*this));
				consume();
			}
		}

		virtual Type getType() const = 0;
		virtual const char* getName() const = 0;
	};
}