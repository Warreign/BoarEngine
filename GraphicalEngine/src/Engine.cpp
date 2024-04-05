#include "Engine.h"

#include "utils/Macros.h"

#include "events/MouseEvent.h"

namespace Warreign
{
	Engine::Engine()
	{
		m_window = std::make_unique<Window>();
		m_window->setEventCallback(EVENT_FUNC(onEvent));

		setup();
	}

	Engine::~Engine()
	{
	}

	void Engine::setup()
	{
		m_renderer = std::make_unique<Renderer>();

		s = std::make_unique<Shader>("assets/shaders/test.vert", "assets/shaders/test.frag");
		t = std::make_unique<Texture>("assets/textures/kanji.png");

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

		vao = std::make_unique<VertexArray>();
		
		VertexBuffer positionVBO(positions, 4, FVEC2);
		vao->addVertexBuffer(positionVBO, 0);
		VertexBuffer colorVBO(colors, 4, FVEC3);
		vao->addVertexBuffer(colorVBO, 2);
		VertexBuffer texCoordVBO(texCoords, 4, FVEC2);
		vao->addVertexBuffer(texCoordVBO, 1);
		ElementBuffer ebo(indices, 6, UINT);
		vao->setElementBuffer(ebo);

		s->setInteger1("uTexture", 1);
		t->bind(1);

		float aspect = float(m_window->getWidth()) / m_window->getHeight();
		float vertical = 2;
		float horizontal = 2 * aspect;
		glm::mat4 MVP = glm::ortho(-horizontal / 2, horizontal / 2, -vertical / 2, vertical / 2);
		s->setMatrix4("mMVP", MVP);
	}

	void Engine::renderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		m_renderer->render(*vao, *s);
	}

	void Engine::onUpdate(double dt)
	{
	}

	void Engine::onEvent(Event& e)
	{
		
		e.handle<WindowCloseEvent>(EVENT_FUNC(Engine::onWindowClose));
		e.handle<WindowResizeEvent>(EVENT_FUNC(Engine::onWindowResize));

	}

	void Engine::onWindowClose(WindowCloseEvent& e)
	{
	}

	void Engine::onWindowResize(WindowResizeEvent& e)
	{
	}

	void Engine::run()
	{
		m_frameTime = glfwGetTime();

		while (m_isRunning)
		{
			double time = glfwGetTime();
			double dt = time - m_frameTime;

			renderScene();
			onUpdate(dt);

			m_window->onUpdate();
		}
	}
}

