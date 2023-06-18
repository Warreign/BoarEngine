#include "Renderer.h"

namespace Warreign
{
	static void glfw_error_callback(int error, const char* description)
	{
		//std::cerr << "ERROR: " << description << std::endl;
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
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD!");
		};
		//gladLoadGL();

		const GLubyte* info = glGetString(GL_VENDOR);
		std::cout << "INFO: Vendor: " << info << std::endl;
		info = glGetString(GL_RENDERER);
		std::cout << "INFO: Renderer: " << info << std::endl;
		info = glGetString(GL_VERSION);
		std::cout << "INFO: Version: " << info << std::endl;

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(opengl_debug_callback, 0);

		glViewport(0, 0, m_windowWidth, m_windowHeight);
		glClearColor(0.2, 0.2 , 0.2, 1.0);
	}

	GLFWwindow* Renderer::getWindow() const
	{
		return m_window;
	}
}

