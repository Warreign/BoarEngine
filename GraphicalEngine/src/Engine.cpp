#include "Engine.h"

namespace Warreign
{
	Engine::Engine()
		: m_renderer(),
		m_frameTime(0), m_isRunning(true),
		s("assets/shaders/test.vert", "assets/shaders/test.frag")
	{
		setup();
	}

	void Engine::setup()
	{
		float positions[] = {
			-0.5,  0.5,
			-0.5, -0.5,
			 0.5, -0.5,
			 0.5,  0.5
		};

		float colors[] = {
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0,
			1.0, 1.0, 1.0
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		
		VertexBuffer positionVBO(positions, 4, FVEC2);
		vao.addVertexBuffer(positionVBO, 0);
		VertexBuffer colorVBO(colors, 4, FVEC3);
		vao.addVertexBuffer(colorVBO, 1);
		ElementBuffer ebo(indices, 6, UINT);
		vao.setElementBuffer(ebo);

		//glCreateBuffers(1, &vbo);
		//glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glCreateVertexArrays(1, &vao);
		//glVertexArrayVertexBuffer(vao, 0, vbo, 0, 5 * sizeof(float));

		//glEnableVertexArrayAttrib(vao, 0);
		//glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		//glVertexArrayAttribBinding(vao, 0, 0);

		//glEnableVertexArrayAttrib(vao, 1);
		//glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
		//glVertexArrayAttribBinding(vao, 1, 0);

		//glCreateBuffers(1, &ebo);
		//glNamedBufferData(ebo, sizeof(indices), indices, GL_STATIC_DRAW);

		//glVertexArrayElementBuffer(vao, ebo);
	}

	void Engine::render()
	{
		s.bind();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		vao.unbind();
		s.unbind();

		glfwSwapBuffers(m_renderer.getWindow());
	}

	void Engine::update(double dt)
	{
	}

	void Engine::run()
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

