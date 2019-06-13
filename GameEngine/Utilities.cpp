#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"
#include "Mesh.h"

//reads a file and returns contents as a string
std::string Utilities::readFile(const std::string& filePath)
{
	//output 
	std::string output; 

	// Open file
	std::ifstream file(filePath);
	
	//if file successfully found
	if (file.is_open())
	{
		// Read file into buffer
		std::stringstream buffer;
		buffer << file.rdbuf();

		//return the contents of buffer
		return buffer.str();
	}
	else
	{
		std::cout << "File '" << filePath << "' not found, and therefore could not be opened! Returned empty string." << std::endl;
		return "";
	}
}