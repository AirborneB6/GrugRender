#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>


/* WIN SPECIFIC
#define ASSERT(x) if (!(x)) __debugbreak();
*/

#define ASSERT(x) if (!(x)) std::cin.ignore();

#define GLCall(x)\
	x;\
	ASSERT(GLLogCall(#x , __FILE__ , __LINE__))

void GLClearErrors();

bool GLLogCall(const char* function, const char* file, unsigned int line);