#include "Asserts.h"

void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, unsigned int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") at: \n" << file << ":" << function << " (" << line << ")." << std::endl;
		return false;
	}

	return true;
}