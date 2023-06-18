#include "ElementBuffer.h"

namespace Warreign
{
	ElementBuffer::ElementBuffer(void* data, int count, DataType type, GLenum usageHint)
		: m_count(count), m_type(type)
	{
		glCreateBuffers(1, &m_id);
		glNamedBufferData(m_id, count * typeSize(type), data, usageHint);
	}

	void ElementBuffer::destroy()
	{
		glDeleteBuffers(1, &m_id);
	}

	const GLuint ElementBuffer::getId() const
	{
		return m_id;
	}
}
