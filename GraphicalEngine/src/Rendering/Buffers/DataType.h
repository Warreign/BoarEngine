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
		case Warreign::NONE:
		case Warreign::BOOLEAN:
		case Warreign::INT:
		case Warreign::FLOAT:
		case Warreign::FVEC2:
		case Warreign::FVEC3:
		case Warreign::FVEC4:
		case Warreign::COUNT:
		default:
			break;
		}
	}
}