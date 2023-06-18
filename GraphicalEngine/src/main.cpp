#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Engine.h"

extern "C" {
	_declspec(dllexport) uint32_t NvOptimusEnablement = 1;
}

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;

	try {
		Warreign::Engine engine;
		engine.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;

		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}