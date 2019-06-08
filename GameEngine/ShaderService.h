#pragma once
#include <string>
#include "glew.h"
#include "boost/container/flat_map.hpp"

//STATIC CLASS
class ShaderService
{
public:
	static void create(const std::string& vertexPath, const std::string& fragmentPath);
	static void activateShaderProgram(std::string& programName);
	static void deleteShaderProgram(std::string& programName);

private:
	static boost::container::flat_map<std::string, size_t> shaderDatabase;
	static size_t createShaderProgram(size_t vertexShader, size_t fragmentShader);
	static size_t compileShader(const std::string& shaderPath, GLenum shaderType);
	static size_t activeShaderProgram;
	static size_t activeVertexShader;
	static size_t activeFragShader;
};

