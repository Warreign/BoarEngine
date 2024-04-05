#include "VertexArray.h"

namespace Warreign
{
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		for (auto VBO : m_vertexBuffers)
		{
			VBO.destroy();
		}
		if (m_elementBuffer.has_value())
			m_elementBuffer.value().destroy();
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::addVertexBuffer(VertexBuffer VBO, int attribIdx)
	{
		int bindingIdx = m_vertexBuffers.size();
		DataType type = VBO.getType();
		glVertexArrayVertexBuffer(m_id, bindingIdx, VBO.getId(), 0, typeSize(type));
		glEnableVertexArrayAttrib(m_id, attribIdx);
		glVertexArrayAttribFormat(m_id, attribIdx, typeElemCount(type), typeEnum(type), GL_FALSE, 0);
		glVertexArrayAttribBinding(m_id, attribIdx, bindingIdx);
		m_vertexBuffers.push_back(VBO);
	}

	void VertexArray::setElementBuffer(ElementBuffer EBO)
	{
		m_elementBuffer = EBO;
		glVertexArrayElementBuffer(m_id, EBO.getId());
	}
	const ElementBuffer& VertexArray::getElementBuffer() const
	{
		assert(m_elementBuffer.has_value());
		return m_elementBuffer.value();
	}
}
