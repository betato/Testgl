#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Read files
	std::string vertexStr = readFile(vertexPath);
	std::string fragmentStr = readFile(fragmentPath);
	const char* vertexCode = vertexStr.c_str();
	const char* fragmentCode = fragmentStr.c_str();
	// Compile
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertex, 1, &vertexCode, NULL);
	glShaderSource(fragment, 1, &fragmentCode, NULL);
	glCompileShader(vertex);
	glCompileShader(fragment);
	// Check for compile errors
	checkShaderErrors(vertex, "VERTEX");
	checkShaderErrors(fragment, "FRAGMENT");
	// Create shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// Check for linking errors
	checkShaderErrors(ID, "PROGRAM");
	// Delete shaders as they are now linked to the program
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

std::string Shader::readFile(const char* filePath)
{
	std::string shaderCode;
	std::ifstream shaderFile;
	// Make sure file stream can throw exceptions
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open and read file
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_READ_FAILED" << std::endl;
	}
	return shaderCode;
}

void Shader::checkShaderErrors(unsigned int ID, const char* type)
{
	int success;
	char infoLog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string & name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
