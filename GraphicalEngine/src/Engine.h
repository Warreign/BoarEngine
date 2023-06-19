#pragma once

#include <stdexcept>

#include "rendering/Renderer.h"

namespace Warreign
{
	class Engine 
	{

	public:
		Engine();


	protected:
		Renderer m_renderer;
		double m_frameTime;
		bool m_isRunning;

		// TMP
	protected:
		VertexArray vao;
		Shader s;
		Texture t;

	protected:
		void setup();
		void renderScene();
		void update(double dt);

	public:
		void run();
	};
	
}

