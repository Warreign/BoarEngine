#pragma once

#include <stdexcept>

#include "rendering/Renderer.h"
#include "rendering/Shader.h"

namespace Warreign
{
	class Engine 
	{

	public:
		Engine();

		// TMP
	protected:
		GLuint vbo;

	protected:
		double m_frameTime;
		bool m_isRunning;
		Renderer m_renderer;

	protected:
		void setup();
		void render();
		void update(double dt);

	public:
		void mainLoop();
	};
	
}

