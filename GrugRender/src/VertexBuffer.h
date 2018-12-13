#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Asserts.h"

class VertexBuffer
{
public:
	 VertexBuffer(const void* data , unsigned int size);
	~ VertexBuffer();

	void bind() const;
	void unbind() const;

	//in a game engine?
	//lock(),
	//setData(),
	//then unlock()

private:

	unsigned int m_RendererID;
};
