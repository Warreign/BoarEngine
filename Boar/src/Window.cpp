#include "Window.h"

#include <stdexcept>
#include <glad/glad.h>

#include "utils/GlDebug.h"
#include "Engine.h"
#include "events/Event.h"
#include "events/MouseEvent.h"
#include "events/KeyEvent.h"
#include "events/WindowEvent.h"

namespace Warreign
{
	static void glfw_error_callback(int error, const char* description)
	{
		throw std::runtime_error(description);
	}

	Window::Window(uint32_t width, uint32_t height, const std::string& title)
		: m_width(width), m_height(height), m_title(title)
	{
		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW!");

		glfwSetErrorCallback(glfw_error_callback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window!");
		}

		initContext();

		if (m_isVsync)
		{
			glfwSwapInterval(1);
		}

		glfwSetWindowUserPointer(m_window, this);

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int state, int mods) 
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (state)
				{
					case GLFW_PRESS:
					{
						MousePressEvent e(button);
						w->eventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseReleaseEvent e(button);
						w->eventCallback(e);
						break;
					}
				}

			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseMoveEvent e(xPos, yPos);
				w->eventCallback(e);
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseScrollEvent e(xOffset, yOffset);
				w->eventCallback(e);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent e;
				w->eventCallback(e);
			});

		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int newWidth, int newHeight)
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				WindowResizeEvent e(newWidth, newHeight);
				w->eventCallback(e);
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressEvent e(key);
						w->eventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent e(key);
						w->eventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyRepeatEvent e(key);
						w->eventCallback(e);
						break;
					}
				}
			});

	}

	Window::~Window()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::initContext()
	{
		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD!");
		};

		std::cout << glGetString(GL_VENDOR) << std::endl;
		std::cout << glGetString(GL_RENDERER) << std::endl;
		std::cout << glGetString(GL_VERSION) << std::endl;

#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback((GLDEBUGPROC)GL_ERROR_CALLBACK, 0);
#endif
	}

	void Window::setVsync(bool value)
	{
		m_isVsync = value;
		if (m_isVsync)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}


}