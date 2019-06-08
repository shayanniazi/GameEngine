#include "ShaderService.h"
#include "Utilities.h"
#include <iostream>

//create and use shader program from user defined vertex and fragment shaders
void ShaderService::create(const std::string& vertexPath, const std::string& fragmentPath)
{
	size_t vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
	size_t fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
	
	size_t shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	glValidateProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//shaderDatabase.insert(std::pair<std::string, size_t>(programName, shaderProgram));

	//since the shader program already has these shaders attached to it, and deleting them will not detatch them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

size_t ShaderService::createShaderProgram(size_t vertexShader, size_t fragmentShader)
{
	//create and link shader program
	size_t shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//error checking
	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR IN SHADER PROGRAM LINKING.\n" << infoLog << std::endl;
	}

	return shaderProgram;
}

size_t ShaderService::compileShader(const std::string& shaderPath, GLenum shaderType)
{
	//load vertex shader file
	std::string sourceCode = Utilities::readFile(shaderPath);
	const char *shaderSource = sourceCode.c_str();

	//create a vertex shader
	size_t shader;
	shader = glCreateShader(shaderType);

	//attach shader source and compile shadre
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	//error checking
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}