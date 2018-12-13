#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "Asserts.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	//UNIFORMS
	int getUniformLocation(const std::string& name);

	void setUniform4f(const std::string& name , float v0 , float v1 , float v2 , float v3);
	void setUniform3f(const std::string& name , float v0, float v1, float v2);
	void setUniform2f(const std::string& name , float v0, float v1);
	void setUniform1f(const std::string& name , float val);

	void setUniform2i(const std::string& name, int v0 , int v1);
	void setUniform1i(const std::string& name, int val);

	void setUniformMat4f(const std::string& name , const glm::mat4& matrix);

	void bind() const;
	void unbind() const;

private:

	unsigned int m_RendererID;

	//INIT
	ShaderSource parseShader(const std::string& filePath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	void createShader(const std::string& vertexShader, const std::string& fragmentShader);

	//CACHING FOR UNIFORMS
	std::unordered_map<std::string, int> m_UniformLocationCache;
};

