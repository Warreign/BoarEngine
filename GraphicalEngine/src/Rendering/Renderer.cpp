#include "Renderer.h"

namespace Warreign
{
	Renderer::Renderer()
	{
		initDevIL();
		glClearColor(0.1, 0.2, 0.5, 1.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Renderer::~Renderer()
	{
		ilShutDown();
	}

	void Renderer::initDevIL()
	{
		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	}

	void Renderer::onWindowResize(int newWidth, int newHeight)
	{
		glViewport(0, 0, newWidth, newHeight);
	}

	void Renderer::render(const VertexArray& VAO, const Shader& shader) const
	{
		const ElementBuffer& EBO = VAO.getElementBuffer();
		shader.bind();
		VAO.bind();
		glDrawElements(GL_TRIANGLES, EBO.getCount(), EBO.getType(), 0);
		VAO.unbind();
		shader.unbind();
			
	}
}

