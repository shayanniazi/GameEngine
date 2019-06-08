#pragma once
#include <string>

class Mesh;

//STATIC CLASS
class ModelLoader
{
public:
	static Mesh loadOBJ(const std::string& filePath);
};

