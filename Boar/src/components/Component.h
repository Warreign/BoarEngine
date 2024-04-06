#pragma once

#include <string>
#include <events/Event.h>

namespace Warreign 
{

	class Component
	{
	public:
		Component(std::string name);

		virtual void onAttach();
		virtual void onDetach();

		virtual void onEvent(Event& e);
		virtual void onUpdate(double dt);

	private:
		std::string m_name;
	};
}
