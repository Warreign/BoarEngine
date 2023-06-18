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


	protected:
		Renderer m_renderer;
		double m_frameTime;
		bool m_isRunning;

		// TMP
	protected:
		//GLuint vbo;
		//GLuint ebo;
		//GLuint vao;
		VertexArray vao;
		Shader s;

	protected:
		void setup();
		void render();
		void update(double dt);

	public:
		void run();
	};
	
}

