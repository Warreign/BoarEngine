#include <iostream>
#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Engine.h"

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;


	try {
		Warreign::Engine engine;
		engine.mainLoop();
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;

		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}