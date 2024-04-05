#pragma once

#include <stdexcept>
#include <memory>

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
		std::unique_ptr<Window> m_window;
		std::unique_ptr<Renderer> m_renderer;

		double m_frameTime = 0;
		bool m_isRunning = true;

		// TMP
	protected:
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<Shader> s;
		std::unique_ptr<Texture> t;

	protected:
		void setup();
		void renderScene();
		void onUpdate(double dt);
		void onEvent(Event& e);
		void invokeEvent(Event& e);

		void onWindowClose(WindowCloseEvent& e);
		void onWindowResize(WindowResizeEvent& e);

	public:
		void run();
	};
	
}

