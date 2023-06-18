#include "VertexBuffer.h"

namespace Warreign
{
	VertexBuffer::VertexBuffer(void* data, int count, DataType type, GLenum usageHint)
		: m_count(count), m_type(type)
	{
		glCreateBuffers(1, &m_id);
		glNamedBufferData(m_id, count * typeSize(type), data, usageHint);
	}

	void VertexBuffer::destroy()
	{
		glDeleteBuffers(1, &m_id);
	}

	//VertexBuffer::~VertexBuffer()
	//{
	//	glDeleteBuffers(1, &m_id);
	//}

	const GLuint VertexBuffer::getId() const
	{
		return m_id;
	}

	const DataType VertexBuffer::getType() const
	{
		return m_type;
	}

	const int VertexBuffer::getCount() const
	{
		return m_count;
	}
}

