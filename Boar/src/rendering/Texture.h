#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>
#include <cstring>

#include <glad/glad.h>
#include <IL/il.h>
#include <IL/ilu.h>

namespace Warreign
{
	class Texture
	{
	public:
		Texture(const std::string& texturePath);
		Texture(int width, int height, GLenum internalFormat = GL_RGBA8);
		~Texture();

		Texture() {}

	private:
		GLuint m_textureID = 0;
		uint8_t* m_data = nullptr;
		int m_width = 0;
		int m_height = 0;
		
		void loadTexture(const std::string& path);

	public:
		void bind(int unit) const;

		void resize(int width, int height, GLenum internalFormat = GL_RGBA8);
		void setData(void* data, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);

		void setFilter(GLenum minFilter, GLenum magFilter);
		void setWrapping(GLenum s, GLenum t, GLenum r = GL_REPEAT);
		void setSwizzle(GLenum r, GLenum g, GLenum b, GLenum a);
		void setSwizzleAll(GLenum val);
		void setParameter(GLenum parameter, GLenum value);
	};
}