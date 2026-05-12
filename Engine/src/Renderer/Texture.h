#pragma once

#include <stb_image.h>
#include <glad/glad.h>

namespace Engine
{
	class Texture 
	{
	public:
		Texture(uint32_t width, uint32_t height, void* data, uint32_t channels = 4);
		explicit Texture(const char* path);

		~Texture();
		
		void Bind(unsigned int slot = 0) const;
	
	private:
		int width, height, channels;
		unsigned int m_RendererID;
		unsigned char* data = nullptr;

	};
}
