#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>


struct VertexBufferElement
{
	unsigned int count;
	unsigned int type; //one of GL_** types
	unsigned char normalized;


	static unsigned int getSizeOfType(unsigned int t)
	{
		switch (t)
		{
			case GL_FLOAT:
				return 4;
				break;
			case GL_UNSIGNED_INT:
				return 4;
				break;
			case GL_UNSIGNED_BYTE:
				return 1;
				break;

			default:
				ASSERT(false);
				return 0;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : stride(0), m_Elements() {};

	template <typename T>
	void push(unsigned int count , unsigned char normalized)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count , unsigned char normalized)
	{
		m_Elements.push_back({count , GL_FLOAT , normalized});
		stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}
	template<>
	void push<unsigned int>(unsigned int count, unsigned char normalized)
	{
		m_Elements.push_back({ count , GL_UNSIGNED_INT , normalized });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
	}
	template<>
	void push<unsigned char>(unsigned int count, unsigned char normalized)
	{
		m_Elements.push_back({ count , GL_UNSIGNED_BYTE , normalized });
		stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	//GETTERS
	inline const std::vector<VertexBufferElement>& getElements() const
	{
		return m_Elements;
	}
	inline unsigned int getStride() const
	{
		return stride;
	}

private:

	std::vector<VertexBufferElement> m_Elements;
	unsigned int stride;

};