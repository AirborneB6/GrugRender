#include "Shader.h"

Shader::Shader(const std::string& filePath)
{
	ShaderSource sources = parseShader(filePath);
	createShader(sources.vertexSource, sources.fragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
	GLCall(glUseProgram(0));
}

ShaderSource Shader::parseShader(const std::string& filePath)
{
	ShaderType type = ShaderType::NONE;

	std::ifstream inFile;
	inFile.open(filePath);

	std::stringstream ss[2];

	std::string line = "";

	while (getline(inFile, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	 return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = GLCall(glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	/*ERROR HANDLING*/
	int result = 0;

	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length = 0;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = new char[length + 1];

		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
		std::cout << message << std::endl;

		delete message;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

void Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	m_RendererID = GLCall(glCreateProgram());
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(m_RendererID, vs));
	GLCall(glAttachShader(m_RendererID, fs));

	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	else
	{
		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

		if (location == -1)
		{
			std::cout << "Warning: uniform \"" << name << "\" doesn't exist!" << std::endl;
		}
		
		m_UniformLocationCache[name] = location;
		return location;
	}
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform3f(const std::string & name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(getUniformLocation(name), v0, v1, v2));
}

void Shader::setUniform2f(const std::string & name, float v0, float v1)
{
	GLCall(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform1f(const std::string & name, float val)
{
	GLCall(glUniform1f(getUniformLocation(name), val));
}

void Shader::setUniform2i(const std::string & name, int v0, int v1)
{
	GLCall(glUniform2i(getUniformLocation(name), v0, v1));
}

void Shader::setUniform1i(const std::string & name, int val)
{
	GLCall(glUniform1i(getUniformLocation(name), val));
}

void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1 , GL_FALSE , &matrix[0][0]));
}
