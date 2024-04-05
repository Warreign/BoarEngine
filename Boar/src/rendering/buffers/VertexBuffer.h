#pragma once

#include "types.h"

namespace Warreign
{
	class VertexBuffer
	{
	public:
		VertexBuffer(void* data, int count, DataType type, GLenum usageHint = GL_STATIC_DRAW);
		void destroy();


	private:
		GLuint m_id = 0;
		int m_count;
		DataType m_type;

	public:
		const GLuint getId() const;
		const DataType getType() const;
		const int getCount() const;
	};
}