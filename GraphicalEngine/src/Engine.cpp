#include "Engine.h"

namespace Warreign
{
	Engine::Engine()
		: m_renderer(),
		m_frameTime(0), m_isRunning(true),
		s("assets/shaders/test.vert", "assets/shaders/test.frag")
		, t("assets/textures/kanji.png")
	{
		setup();
	}

	Engine::~Engine()
	{
	}

	void Engine::setup()
	{
		float positions[] = {
			-0.5,  0.5,
			-0.5, -0.5,
			 0.5, -0.5,
			 0.5,  0.5
		};

		float texCoords[] = {
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0
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
		vao.addVertexBuffer(colorVBO, 2);
		VertexBuffer texCoordVBO(texCoords, 4, FVEC2);
		vao.addVertexBuffer(texCoordVBO, 1);
		ElementBuffer ebo(indices, 6, UINT);
		vao.setElementBuffer(ebo);

		s.setInteger1("uTexture", 1);
		t.bind(1);

		float aspect = float(m_window.getWidth()) / m_window.getHeight();
		float vertical = 2;
		float horizontal = 2 * aspect;
		glm::mat4 MVP = glm::ortho(-horizontal / 2, horizontal / 2, -vertical / 2, vertical / 2);
		s.setMatrix4("mMVP", MVP);
	}

	void Engine::renderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		m_renderer.render(vao, s);
	}

	void Engine::update(double dt)
	{
	}

	void Engine::run()
	{
		m_frameTime = glfwGetTime();

		while (m_isRunning && !glfwWindowShouldClose(m_window.getHandle()))
		{
			double time = glfwGetTime();
			double dt = time - m_frameTime;

			renderScene();
			update(dt);

			m_window.onUpdate();
		}
	}
}

