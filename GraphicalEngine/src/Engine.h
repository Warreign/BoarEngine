#pragma once

#include <stdexcept>

#include "rendering/Renderer.h"
#include "Window.h"
#include "events/WindowEvent.h"

namespace Warreign
{
	class Engine 
	{

	public:
		Engine();
		~Engine();

	protected:
		Window m_window;
		Renderer m_renderer;

		double m_frameTime = 0;
		bool m_isRunning = true;

		// TMP
	protected:
		VertexArray vao;
		Shader s;
		Texture t;

	protected:
		void setup();
		void renderScene();
		void onUpdate(double dt);
		void onEvent(Event& e);

		void onWindowClose(WindowCloseEvent& e);
		void onWindowResize(WindowResizeEvent& e);

	public:
		void run();
	};
	
}

