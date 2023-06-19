#include "Renderer.h"

namespace Warreign
{
	static void glfw_error_callback(int error, const char* description)
	{
		throw std::runtime_error(description);
	}

	static void GLAPIENTRY opengl_debug_callback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	Renderer::Renderer()
	{
		initWindow();
		initOpenGL();
		initDevIL();
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
		ilShutDown();
	}

	void Renderer::initWindow()
	{
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, WINDOW_TITLE, NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);
	}

	void Renderer::initOpenGL()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD!");
		};

		std::cout << glGetString(GL_VENDOR) << std::endl;
		std::cout << glGetString(GL_RENDERER) << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(opengl_debug_callback, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, m_windowWidth, m_windowHeight);
		glClearColor(0.1, 0.2, 0.3, 1.0);
	}

	void Renderer::initDevIL()
	{
		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	}

	void Renderer::render(const VertexArray& VAO, const Shader& shader) const
	{
		const ElementBuffer& EBO = VAO.getElementBuffer();
		shader.bind();
		VAO.bind();
		glDrawElements(GL_TRIANGLES, EBO.getCount(), EBO.getType(), 0);
		VAO.unbind();
		shader.unbind();
			
	}

	GLFWwindow* Renderer::getWindow() const
	{
		return m_window;
	}

	int Renderer::getWindowWidth() const
	{
		return m_windowWidth;
	}

	int Renderer::getWindowHeight() const
	{
		return m_windowHeight;
	}
}

