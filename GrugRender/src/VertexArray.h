#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer& buffer , const VertexBufferLayout& layout);
	void setLayout(VertexBufferLayout& layout); //UNNEEDED?

	void bind() const;
	void unbind() const;

private:

	unsigned int m_RendererID;

};