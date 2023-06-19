#include "Texture.h"

namespace Warreign
{
	Texture::Texture(const std::string& texturePath)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);

		loadTexture(texturePath);
		glTextureStorage2D(m_textureID, 1, GL_RGBA8, m_width, m_height);
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

		glTextureParameteri(m_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture::Texture(int width, int height, GLenum internalFormat)
		: m_data(nullptr), m_width(width), m_height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_textureID);
		glTextureStorage2D(m_textureID, 1, internalFormat, width, height);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
		delete[] m_data;
	}

	void Texture::loadTexture(const std::string& path)
	{
		ILuint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		std::wstring wpath(path.begin(), path.end());
		const wchar_t* path_ptr = wpath.c_str();
		if (ilLoadImage(path_ptr) == IL_FALSE)
		{
			throw std::runtime_error("Texture " + path + " failed to load," + std::to_string(ilGetError()) + "!\n");
		}

		m_width = ilGetInteger(IL_IMAGE_WIDTH);
		m_height = ilGetInteger(IL_IMAGE_HEIGHT);
		m_data = new uint8_t[m_width * m_height * 4];
		ilCopyPixels(0, 0, 0, m_width, m_height, 1, IL_RGBA, IL_UNSIGNED_BYTE, m_data);

		ilBindImage(0);
		ilDeleteImages(1, &imgID);
	}

	void Texture::bind(int unit) const
	{
		glBindTextureUnit(unit, m_textureID);
	}

	void Texture::setData(void* data, GLenum format, GLenum type)
	{
		glTextureSubImage2D(m_textureID, 0, 0, 0, m_width, m_height, format, type, data);
		std::memcpy(m_data, data, m_width * m_height);
	}

}
