#pragma once

#include <iostream>
#include <fstream>
#include <streambuf>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Warreign
{
	class Shader
	{
	protected:
		static inline const std::string GLSL_VERSION = "#version 460 core\n";

	public:
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		Shader(const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragmentShaderPath);
		~Shader();

	protected:
		std::string m_vertPath, m_fragPath;
		GLuint m_programID;

		struct AttributeLocations
		{
			GLint position = -1;
			GLint color = -1;
		} m_attributes;

		struct UniformLocations
		{
		} m_uniforms;

		static const std::string readShaderFromFile(const std::string& path);
		static const GLuint compileShader(GLenum type, const std::string& path);

	public:
		void bind() const;
		void unbind() const;

	public:
		GLint attributeLocation(const std::string& name) const;
		GLint uniformLocation(const std::string& name) const;

	public:
		void setInteger1(GLint uniform, int value) const;
		void setInteger2(GLint uniform, const glm::ivec2& value) const;
		void setInteger3(GLint uniform, const glm::ivec3& value) const;
		void setInteger4(GLint uniform, const glm::ivec4& value) const;

		void setFloat1(GLint uniform, float value) const;
		void setFloat2(GLint uniform, const glm::vec2& value) const;
		void setFloat3(GLint uniform, const glm::vec3& value) const;
		void setFloat4(GLint uniform, const glm::vec4& value) const;

		void setMatrix3(GLint uniform, const glm::mat3& value) const;
		void setMatrix4(GLint uniform, const glm::mat4& value) const;

		void setInteger1(const std::string& uniformName, int value) const;
		void setInteger2(const std::string& uniformName, const glm::ivec2& value) const;
		void setInteger3(const std::string& uniformName, const glm::ivec3& value) const;
		void setInteger4(const std::string& uniformName, const glm::ivec4& value) const;

		void setFloat1(const std::string& uniformName, float value) const;
		void setFloat2(const std::string& uniformName, const glm::vec2& value) const;
		void setFloat3(const std::string& uniformName, const glm::vec3& value) const;
		void setFloat4(const std::string& uniformName, const glm::vec4& value) const;

		void setMatrix3(const std::string& uniformName, const glm::mat3& value) const;
		void setMatrix4(const std::string& uniformName, const glm::mat4& value) const;
	};

}