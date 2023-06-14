#pragma once

#include <stdexcept>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Warreign
{
	class Renderer
	{
	public:
		Renderer();

	protected:
		// Window related variables
		const int OPENGL_VERSION_MAJOR = 4;
		const int OPENGL_VERSION_MINOR = 6;

		int m_windowWidth = 1280;
		int m_windowHeight = 720;

		const char* WINDOW_TITLE = "Graphical Engine";

		GLFWwindow* m_window;

	protected:

		void initWindow();


	public:
		GLFWwindow* getWindow() const;
	}; 
}