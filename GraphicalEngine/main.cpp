#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;

	glm::vec3 vector = {1, 2, 3};
	std::cout << vector.x << std::endl;

	return EXIT_SUCCESS;
}