#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Warreign
{
	class Window
	{
	public:
		Window(uint32_t width = 1280, uint32_t height = 960, const std::string& title = "Window");
		~Window();

	private:
		GLFWwindow* m_window;

		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;
		bool m_isVsync = true;

		void initContext();

	public:
		void onUpdate();

		GLFWwindow* getHandle() const { return m_window; }
		bool isVsync() const { return m_isVsync; }
		void setVsync(bool value);

		uint32_t getWidth() const { return m_width; }
		uint32_t getHeight() const { return m_height; }
		const std::string& getTitle() const { return m_title; }
	};
}