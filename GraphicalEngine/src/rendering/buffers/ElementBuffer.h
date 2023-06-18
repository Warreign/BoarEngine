#pragma once

#include "types.h"

namespace Warreign
{
	class ElementBuffer
	{
	public:
		ElementBuffer(void* data, int count, DataType type, GLenum usageHint = GL_STATIC_DRAW);
		void destroy();

	private:
		GLuint m_id = 0;
		int m_count;
		DataType m_type;

	public:
		const GLuint getId() const;

	};
}