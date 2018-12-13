#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Asserts.h"

class IndexBuffer
{
public:
	 IndexBuffer(const unsigned int* data , unsigned int count);
	~ IndexBuffer();

	void bind() const;
	void unbind() const;

	unsigned int getCount() const;

	//in a game engine?
	//lock(),
	//setData(),
	//then unlock()

private:

	unsigned int m_RendererID;
	unsigned int m_Count;
};
