#include "Engine.h"

namespace Warreign
{
	Engine::Engine()
		: m_renderer(),
		m_frameTime(0), m_isRunning(true)
	{
		setup();
	}

	void Engine::setup()
	{
		glGenBuffers(1, &vbo);
		
		Shader s("Shader/text.vs", "Shader/test.fs");
	}

	void Engine::render()
	{
	}

	void Engine::update(double dt)
	{
	}

	void Engine::mainLoop()
	{
		m_frameTime = glfwGetTime();

		while (m_isRunning && !glfwWindowShouldClose(m_renderer.getWindow()))
		{
			double time = glfwGetTime();
			double dt = time - m_frameTime;

			glfwPollEvents();

			render();
			update(dt);
		}
	}
}

