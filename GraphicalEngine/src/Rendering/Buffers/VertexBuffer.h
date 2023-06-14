#pragma once

#include "DataType.h"

namespace Warreign
{
	class VertexBuffer
	{

	protected:
		GLuint handle;
		int count;

	public:
		VertexBuffer(void* data, int count, DataType type, GLenum usageHint = GL_STATIC_DRAW);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		int getCount() const;
	};
}