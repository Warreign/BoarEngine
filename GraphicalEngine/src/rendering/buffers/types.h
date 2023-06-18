#pragma once

#include <stdexcept>
#include <glad/glad.h>

namespace Warreign
{

	enum DataType
	{
		NONE,
		BOOLEAN,
		INT,
		UINT,
		FLOAT,
		FVEC2,
		FVEC3,
		FVEC4,
		COUNT
	};

	static long typeSize(DataType type)
	{
		switch (type)
		{
		case BOOLEAN:
			return sizeof(bool);
		case INT:
			return sizeof(int);
		case UINT:
			return sizeof(unsigned int);
		case FLOAT:
			return sizeof(float);
		case FVEC2:
			return 2 * sizeof(float);
		case FVEC3:
			return 3 * sizeof(float);
		case FVEC4:
			return 4 * sizeof(float);
		default:
			throw std::runtime_error("Wrong data type!");
		}
		return 0;
	}

	static long typeEnum(DataType type)
	{
		switch (type)
		{
		case BOOLEAN:
			return GL_INT;
		case INT:
			return GL_INT;
		case UINT:
			return GL_UNSIGNED_INT;
		case FLOAT:
			return GL_FLOAT;
		case FVEC2:
			return GL_FLOAT;
		case FVEC3:
			return GL_FLOAT;
		case FVEC4:
			return GL_FLOAT;
		default:
			throw std::runtime_error("Wrong data type!");
		}
	}

	static long typeElemCount(DataType type)
	{
		switch (type)
		{
		case BOOLEAN:
			return 1;
		case INT:
			return 1;
		case UINT:
			return 1;
		case FLOAT:
			return 1;
		case FVEC2:
			return 2;
		case FVEC3:
			return 3;
		case FVEC4:
			return 4;
		default:
			throw std::runtime_error("Wrong data type!");
		}
	}
}