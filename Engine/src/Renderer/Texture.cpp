#include "enpch.h"
#include "Texture.h"
#include "../Engine/Core/Log.h"

namespace Engine
{
	Texture::Texture(const char* path)
	{
		stbi_set_flip_vertically_on_load(1);
		data = stbi_load(path, &width, &height, &channels, 0);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Format Detection
		GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

		// Upload to GPU
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			EN_CORE_ERROR("FAILED TO LOAD TEXTURE!");
		}

		EN_CORE_WARN("Texture Loaded: {0}x{1}", width, height);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}