#pragma once

namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		void Bind() const;
		void Unbind() const;

	private:
		std::string ReadFile(const std::string& path);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath);

	private:
		unsigned int m_RendererID;

	};
}
