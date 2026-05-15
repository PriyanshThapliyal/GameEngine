#include "enpch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "../Engine/Core/Log.h"

namespace Engine
{
	Texture::Texture(uint32_t width, uint32_t height, void* data, uint32_t channels)
		: width(width), height(height), channels(channels)
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}

	Texture::Texture(const char* path)
		: Texture(std::string(path))
	{
	}

	Texture::Texture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		channels = 4;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Upload to GPU
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);
			EN_CORE_WARN("Texture Loaded: {0} ({1}x{2})", path, width, height);
		}
		else
		{
			width = 1;
			height = 1;
			channels = 4;
			uint32_t fallbackData = 0xffff00ff;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &fallbackData);
			EN_CORE_ERROR("Failed to load texture '{0}': {1}", path, stbi_failure_reason());
		}

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		if (m_RendererID)
			glDeleteTextures(1, &m_RendererID);
	}

	Texture::Texture(Texture&& other) noexcept
		: width(other.width), height(other.height), channels(other.channels), m_RendererID(other.m_RendererID)
	{
		other.width = 0;
		other.height = 0;
		other.channels = 0;
		other.m_RendererID = 0;
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			if (m_RendererID)
				glDeleteTextures(1, &m_RendererID);

			width = other.width;
			height = other.height;
			channels = other.channels;
			m_RendererID = other.m_RendererID;

			other.width = 0;
			other.height = 0;
			other.channels = 0;
			other.m_RendererID = 0;
		}

		return *this;
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}
