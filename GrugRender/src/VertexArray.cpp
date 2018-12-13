#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer & buffer, const VertexBufferLayout & layout)
{
	buffer.bind();
	const std::vector<VertexBufferElement>& elems = layout.getElements();
	unsigned int offset = 0;

	//index size type normalized stride pointer - parms required by glVertexAttribPointer
	for (unsigned int i = 0; i < elems.size(); i++)
	{
		const VertexBufferElement& elem = elems[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.getStride(), (const void*)offset));
		


		offset += elem.count * VertexBufferElement::getSizeOfType(elem.type);
	}
}

void VertexArray::setLayout(VertexBufferLayout & layout)
{
	//UNNEEDED?
}

void VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}
