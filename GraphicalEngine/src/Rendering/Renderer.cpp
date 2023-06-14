#include "Renderer.h"

namespace Warreign
{
	static void glfw_error_callback(int error, const char* description)
	{
		std::cerr << "ERROR: " << description << std::endl;
	}

	Renderer::Renderer()
	{
		initWindow();
	}

	void Renderer::initWindow()
	{
		glfwSetErrorCallback(glfw_error_callback);

		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, WINDOW_TITLE, NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(m_window);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		gladLoadGL();

		glClearColor(0, 0, 0, 1);
	}

	GLFWwindow* Renderer::getWindow() const
	{
		return m_window;
	}
}

