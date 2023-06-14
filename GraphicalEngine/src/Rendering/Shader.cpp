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

		std::cout << shaderSource << std::endl;
		exit(123);

		return std::string();
	}

	Shader::Shader(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename)
		: m_vertFilename(vertexShaderFilename), m_fragFilename(fragmentShaderFilename), m_programID(0)
	{
		GLint success;

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexSource(GLSL_VERSION);
		vertexSource += readShaderFromFile(vertexShaderFilename);

		std::string fragmentSource(GLSL_VERSION);
		fragmentSource += readShaderFromFile(fragmentShaderFilename);

		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


	}

	Shader::~Shader()
	{
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

