#pragma once

#include <vector>
#include <optional>
#include <cassert>
#include "types.h"

#include "VertexBuffer.h"
#include "ElementBuffer.h"

namespace Warreign
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

	private:
		GLuint m_id = 0;
		std::vector<VertexBuffer> m_vertexBuffers;
		std::optional<ElementBuffer> m_elementBuffer;

	public:
		void bind() const;
		void unbind() const;

		void addVertexBuffer(VertexBuffer VBO, int attribIdx);
		void setElementBuffer(ElementBuffer EBO);

		const ElementBuffer& getElementBuffer() const;
	};
}