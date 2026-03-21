#pragma once

#include <string>
#include <unordered_map>

namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		// Prevents copying of Shader
		Shader(const Shader&) = delete;
		Shader& operator = (const Shader&) = delete;

		void Bind() const;
		void Unbind() const;

		//Uniforms
		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat4(const std::string& name, float v0, float v1, float v2, float v3);

	private:
		std::string ReadFile(const std::string& path);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath);
		int GetUniformLocation(const std::string& name);
	
	private:
		unsigned int m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}
