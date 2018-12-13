#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

#include "stb_image/stb_image.h"
#include "Asserts.h"

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	const int& getWidth() const;
	const int& getHeight() const;

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:

	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;

	int m_Width, m_Height, m_BPP;

};