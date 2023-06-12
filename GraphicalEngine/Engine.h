#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Rendering/Renderer.h"

namespace Warreign
{
	class Engine 
	{
	public:
		//static Engine& instance;

	public:
		Engine();

	protected:
		Renderer renderer;


	public:
		void mainLoop();
	};
}

