#include "Shader.h"

namespace Warreign
{
	const std::string Shader::readShaderFromFile(const std::string& path)
	{
		std::ifstream fs(path);
		std::string shaderSource;

		fs.seekg(0, std::ios::end);
		shaderSource.reserve(fs.tellg());
		fs.seekg(0, std::ios::beg);

		shaderSource.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
		fs.close();

		return shaderSource;
	}

	const GLuint Shader::compileShader(GLenum type, const std::string& path)
	{
		GLint result;
		GLuint shader = glCreateShader(type);

		std::string shaderSource(GLSL_VERSION);
		shaderSource += readShaderFromFile(path);

		const GLchar* source = shaderSource.c_str();
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

			GLchar* message = new GLchar[logSize];
			glGetShaderInfoLog(shader, logSize, &logSize, message);

			std::cerr << "ERROR: Shader " << path << " failed to compile: " << std::endl;
			std::cerr << message << std::endl;

			glDeleteShader(shader);
			delete[] message;
			return 0;
		}
		
		return shader;
	}

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
		: m_vertPath(vertexShaderPath), m_fragPath(fragmentShaderPath), m_programID(0)
	{
		GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
		assert(vertexShader != 0);
		GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
		assert(fragmentShader != 0);

		m_programID = glCreateProgram();

		glAttachShader(m_programID, vertexShader);
		glAttachShader(m_programID, fragmentShader);
		glLinkProgram(m_programID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		GLint result;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logSize;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logSize);

			GLchar* message = new GLchar[logSize];
			glGetProgramInfoLog(m_programID, logSize, &logSize, message);

			std::cerr << "ERROR: Program " << vertexShaderPath << "/" << fragmentShaderPath << " failed to link: " << std::endl;
			std::cerr << message << std::endl;

			glDeleteProgram(m_programID);
			delete[] message;
		}
	}

	Shader::Shader(const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragmentShaderPath)
	{
		GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
		assert(vertexShader != 0);
		GLuint geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryShaderPath);
		assert(geometryShader != 0);
		GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
		assert(fragmentShader != 0);

		m_programID = glCreateProgram();

		glAttachShader(m_programID, vertexShader);
		glAttachShader(m_programID, geometryShader);
		glAttachShader(m_programID, fragmentShader);
		glLinkProgram(m_programID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(geometryShader);

		GLint result;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logSize;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logSize);

			GLchar* message = new GLchar[logSize];
			glGetProgramInfoLog(m_programID, logSize, &logSize, message);

			std::cerr << "ERROR: Program " << vertexShaderPath << "/" << geometryShaderPath << "/" << fragmentShaderPath << " failed to link: " << std::endl;
			std::cerr << message << std::endl;

			glDeleteProgram(m_programID);
			delete[] message;
		}
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programID);
	}

	void Shader::bind() const
	{
		glUseProgram(m_programID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	GLint Shader::attributeLocation(const std::string& name) const
	{
		GLint location = glGetAttribLocation(m_programID, name.c_str());
		if (location == -1)
			std::cout << "WARN: Attribute " << name << " could not be found in shaders " << m_vertPath << "/" << m_fragPath << "." << std::endl;
		return location;
	}

	GLint Shader::uniformLocation(const std::string& name) const
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		if (location == -1)
			std::cout << "WARN: Uniform " << name << " could not be found in shaders " << m_vertPath << "/" << m_fragPath << "." << std::endl;
		return location;
	}

	void Shader::setInteger1(GLint uniform, int value) const
	{
		glProgramUniform1i(m_programID, uniform, value);
	}

	void Shader::setInteger2(GLint uniform, const glm::ivec2& value) const
	{
		glProgramUniform2i(m_programID, uniform, value.x, value.y);
	}

	void Shader::setInteger3(GLint uniform, const glm::ivec3& value) const
	{
		glProgramUniform3i(m_programID, uniform, value.x, value.y, value.z);
	}

	void Shader::setInteger4(GLint uniform, const glm::ivec4& value) const
	{
		glProgramUniform4i(m_programID, uniform, value.x, value.y, value.z, value.w);
	}

	void Shader::setFloat1(GLint uniform, float value) const
	{
		glProgramUniform1f(m_programID, uniform, value);
	}

	void Shader::setFloat2(GLint uniform, const glm::vec2& value) const
	{
		glProgramUniform2f(m_programID, uniform, value.x, value.y);
	}

	void Shader::setFloat3(GLint uniform, const glm::vec3& value) const
	{
		glProgramUniform3f(m_programID, uniform, value.x, value.y, value.z);
	}

	void Shader::setFloat4(GLint uniform, const glm::vec4& value) const
	{
		glProgramUniform4f(m_programID, uniform, value.x, value.y, value.z, value.w);
	}

	void Shader::setMatrix3(GLint uniform, const glm::mat3& value) const
	{
		glProgramUniformMatrix3fv(m_programID, uniform, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setMatrix4(GLint uniform, const glm::mat4& value) const
	{
		glProgramUniformMatrix4fv(m_programID, uniform, 1, GL_FALSE, glm::value_ptr(value));
	}



	void Shader::setInteger1(const std::string& uniformName, int value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform1i(m_programID, location, value);
	}

	void Shader::setInteger2(const std::string& uniformName, const glm::ivec2& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform2i(m_programID, location, value.x, value.y);
	}

	void Shader::setInteger3(const std::string& uniformName, const glm::ivec3& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform3i(m_programID, location, value.x, value.y, value.z);
	}

	void Shader::setInteger4(const std::string& uniformName, const glm::ivec4& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform4i(m_programID, location, value.x, value.y, value.z, value.w);
	}

	void Shader::setFloat1(const std::string& uniformName, float value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform1f(m_programID, location, value);
	}

	void Shader::setFloat2(const std::string& uniformName, const glm::vec2& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform2f(m_programID, location, value.x, value.y);
	}

	void Shader::setFloat3(const std::string& uniformName, const glm::vec3& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform3f(m_programID, location, value.x, value.y, value.z);
	}

	void Shader::setFloat4(const std::string& uniformName, const glm::vec4& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniform4f(m_programID, location, value.x, value.y, value.z, value.w);
	}

	void Shader::setMatrix3(const std::string& uniformName, const glm::mat3& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniformMatrix3fv(m_programID, location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setMatrix4(const std::string& uniformName, const glm::mat4& value) const
	{
		GLint location = uniformLocation(uniformName);	
		glProgramUniformMatrix4fv(m_programID, location, 1, GL_FALSE, glm::value_ptr(value));
	}

}
