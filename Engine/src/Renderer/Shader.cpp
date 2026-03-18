#include "enpch.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include "Engine/Core/Log.h"

namespace Engine
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		m_RendererID = CreateShader(vertexPath, fragmentPath);
	}

	std::string Shader::ReadFile(const std::string& path)
	{
		std::ifstream file(path);
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

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int length;
			std::vector<char> message(length);
			glGetShaderInfoLog(id, length, &length, &message[0]);

			EN_CORE_FATAL("Shader compilation failed :\n", &message[0]);
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
		glValidateProgram(program);

		glDeleteShader(fs);
		glDeleteShader(vs);

		return program;

	}
}