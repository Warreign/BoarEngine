#pragma once

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IL/il.h>

#include "buffers/VertexArray.h"
#include "Texture.h"
#include "Shader.h"

namespace Warreign
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

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
		void initOpenGL();
		void initDevIL();

	public:
		void render(const VertexArray& VAO, const Shader& shader) const;

	public:
		GLFWwindow* getWindow() const;
		int getWindowWidth() const;
		int getWindowHeight() const;
	}; 
}