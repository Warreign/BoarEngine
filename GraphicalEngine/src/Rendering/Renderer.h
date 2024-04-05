#pragma once

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
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
		void initDevIL();

	public:
		void render(const VertexArray& VAO, const Shader& shader) const;
		void onWindowResize(int newWidth, int newHeight);
	}; 
}