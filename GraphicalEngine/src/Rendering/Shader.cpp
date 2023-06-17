#include "Shader.h"

namespace Warreign
{
	const std::string Shader::readShaderFromFile(const std::string& filename)
	{
		std::ifstream fs(filename);
		std::string shaderSource;

		fs.seekg(0, std::ios::end);
		shaderSource.reserve(fs.tellg());
		fs.seekg(0, std::ios::beg);

		shaderSource.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());

		//std::cout << shaderSource << std::endl;
		//exit(123);
		fs.close();

		return shaderSource;
	}

	const GLuint Shader::compileShader(GLenum type, const std::string& filename)
	{
		GLint result;
		GLuint shader = glCreateShader(type);

		std::string shaderSource(GLSL_VERSION);
		shaderSource += readShaderFromFile(filename);

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

			std::cerr << "ERROR: Shader " << filename << " failed to compile: " << std::endl;
			std::cerr << message << std::endl;

			glDeleteShader(shader);
			delete[] message;
			return 0;
		}
		
		return shader;
	}

	Shader::Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
		: m_vertFilename(vertexShaderFilename), m_fragFilename(fragmentShaderFilename), m_programID(0)
	{
		GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderFilename);
		GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

		assert(vertexShader != 0);
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

			std::cerr << "ERROR: Program " << vertexShaderFilename << "/" << fragmentShaderFilename << " failed to link: " << std::endl;
			std::cerr << message << std::endl;

			glDeleteProgram(m_programID);
			delete[] message;
		}
	}

	Shader::Shader(const std::string& vertexShaderFilename, const std::string& geometryShaderFilename, const std::string& fragmentShaderFilename)
	{
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
			std::cout << "WARN: Attribute " << name << " could not be found in shaders " << m_vertFilename << "/" << m_fragFilename << "." << std::endl;
		return location;
	}

	GLint Shader::uniformLocation(const std::string& name) const
	{
		GLint location = glGetUniformLocation(m_programID, name.c_str());
		if (location == -1)
			std::cout << "WARN: Uniform " << name << " could not be found in shaders " << m_vertFilename << "/" << m_fragFilename << "." << std::endl;
		return location;
	}


}

