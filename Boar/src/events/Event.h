#pragma once

namespace Warreign
{
	class Event
	{
#define EVENT_TYPE(type) public:\
							virtual Type getType() const { return type; }\
							virtual const char* getName() const { return #type; }\
							static Type getStaticType() { return type; }
	public:
		enum Type
		{
			WindowClose, WindowResize,
			MousePress, MouseRelease, MouseScroll, MouseMove,
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

	using EventCallback = std::function<void(Event&)>;

}