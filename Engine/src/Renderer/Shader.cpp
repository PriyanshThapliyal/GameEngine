#include "enpch.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include "Engine/Core/Log.h"


namespace Engine
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		m_RendererID = CreateShader(vertexPath, fragmentPath);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string Shader::ReadFile(const std::string& path)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			EN_CORE_FATAL("Failed to open shader file: {0}", path);
		}
		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		GLint isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

			std::cout << infoLog.data() << std::endl;

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc = ReadFile(vertexPath);
		std::string fragmentSrc = ReadFile(fragmentPath);

		unsigned int program = glCreateProgram();

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		
		glLinkProgram(program);

		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> message(length);
			glGetProgramInfoLog(program, length, &length, message.data());

			EN_CORE_FATAL("Shader linking failed:\n{0}", message.data());
		}
		glValidateProgram(program);

		glDeleteShader(fs);
		glDeleteShader(vs);

		return program;

	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];
		
		int location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1)
			EN_CORE_WARN("Uniform '{0}' not found!", name);

		m_UniformLocationCache[name] = location;
		return location;
	}

	void Shader::SetUniformFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniformFloat4(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
}