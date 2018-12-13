#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Asserts.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
public:
	void draw(const VertexArray& va , const IndexBuffer& ib , const Shader& shader) const;
	void clear() const;

private:



};