#pragma once

#include <stb_image.h>
#include <glad/glad.h>
#include <cstdint>
#include <string>

namespace Engine
{
	class Texture 
	{
	public:
		Texture(uint32_t width, uint32_t height, void* data, uint32_t channels = 4);
		explicit Texture(const char* path);
		explicit Texture(const std::string& path);

		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
		
		void Bind(unsigned int slot = 0) const;
	
	private:
		int width = 0, height = 0, channels = 0;
		unsigned int m_RendererID = 0;

	};
}
