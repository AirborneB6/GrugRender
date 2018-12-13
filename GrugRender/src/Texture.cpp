#include "Texture.h"

Texture::Texture(const std::string& filePath) : 
	m_RendererID(0) , m_FilePath(filePath) , m_LocalBuffer(nullptr) , 
	m_Width(0) , m_Height(0) , m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	//set minification and magnification filters
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//set clamping of protruding edges (instead of tiling)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//supply buffer to GPU
	GLCall(glTexImage2D(GL_TEXTURE_2D,0 , GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

	//unbind
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	//(optional) clear CPU buffer
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}
}

Texture::~Texture()
{
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr;
	}

	GLCall(glDeleteTextures(1, &m_RendererID));
}

const int& Texture::getWidth() const
{
	return m_Width;
}

const int& Texture::getHeight() const
{
	return m_Height;
}

void Texture::bind(unsigned int slot /* = 0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
