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

//loads OBJ files (blender files)
Mesh Utilities::loadOBJ(const std::string& filePath)
{
	std::string file = Utilities::readFile(filePath);
	
	if (file == "")
	{
		std::cout << "Not able to load OBJ file: " << filePath << std::endl;
		return Mesh();
	}

	//convert string to a string vector that contains line by line data
	std::vector<std::string> objFile;
	std::string line;

	for (size_t i = 0; i < file.size(); i++)
	{
		//if you encounter a '\n', append into line data
		if (file.at(i) == '\n')
		{
			objFile.push_back(line);
			line.clear();
		}
		//if at last line of file, since the last line doesn't have a '\n' character in it, we have to do this:
		else if (i == file.size() - 1)
		{
			objFile.push_back(line);
			line.clear();
		}
		else
			line.push_back(file.at(i));
	}

	//clear last line
	line.clear();

	std::string word;
	std::vector<std::string> lineWords;
	std::vector<Vec3> vertices;
	std::vector<Vec2> textCoords;
	std::vector<Vec3> normals;
	std::vector<std::string> faceData;
	std::vector<size_t> vertIndices;
	std::vector<size_t> uvIndices;
	std::vector<size_t> normIndices;

	//for each and every line
	for (size_t i = 0; i < objFile.size(); i++)
	{
		//parse the line whose 1st character is 'v'
		if (objFile.at(i).front() == 'v')
		{
			//if 2nd character in line is empty space, then it is a vertex coordinate, and parse it as such
			if (objFile.at(i).at(1) == ' ')
			{
				//loop through the vertex coordinates containing line
				for (size_t j = 2; j < objFile.at(i).size(); j++)
				{
					if (objFile.at(i).at(j) == ' ')
					{
						lineWords.push_back(word);
						word.clear();
					}
					//check if we're at the last character
					else if (j == objFile.at(i).size() - 1)
					{
						lineWords.push_back(word);
						word.clear();

						//once the line is complete, append all 3 vertex 'words' from the lineWords vector into result vector
						float x = std::stof(lineWords.at(0));
						float y = std::stof(lineWords.at(1));
						float z = std::stof(lineWords.at(2));
						vertices.push_back(Vec3(x, y, z));

						lineWords.clear();
					}
					//if no empty space and if we're not at the last char of the line, continue on storing data char by char
					else
						word.push_back(objFile.at(i).at(j));
				}
			}
			else if (objFile.at(i).at(1) == 't')
			{
				for (size_t j = 3; j < objFile.at(i).size(); j++)
				{
					//if empty space occurs in line, then store word (aka vertex coordinate)
					if (objFile.at(i).at(j) == ' ')
					{
						lineWords.push_back(word);
						word.clear();
					}
					//check if we're at the last character
					else if (j == objFile.at(i).size() - 1)
					{

						lineWords.push_back(word);
						word.clear();

						//once the line is complete, append all 3 vertex 'words' from the lineWords vector into result vector
						float x = std::stof(lineWords.at(0));
						float y = std::stof(lineWords.at(1));
						textCoords.push_back(Vec2(x, y));

						lineWords.clear();
					}
					//if no empty space, continue on storing data char by char
					else
						word.push_back(objFile.at(i).at(j));
				}
			}
			else if (objFile.at(i).at(1) == 'n')
			{
				for (size_t j = 3; j < objFile.at(i).size(); j++)
				{
					//if empty space occurs in line, then store word (aka vertex coordinate)
					if (objFile.at(i).at(j) == ' ')
					{
						lineWords.push_back(word);
						word.clear();
					}
					//check if we're at the last character
					else if (j == objFile.at(i).size() - 1)
					{
						lineWords.push_back(word);
						word.clear();

						//once the line is complete, append all 3 vertex 'words' from the lineWords vector into result vector
						float x = std::stof(lineWords.at(0));
						float y = std::stof(lineWords.at(1));
						float z = std::stof(lineWords.at(2));
						normals.push_back(Vec3(x, y, z));

						lineWords.clear();
					}
					//if no empty space, continue on storing data char by char
					else
						word.push_back(objFile.at(i).at(j));
				}
			}
		}
		//parse face data
		else if (objFile.at(i).front() == 'f')
		{
			for (size_t j = 2; j < objFile.at(i).size(); j++)
			{
				//if empty space occurs in line, then store word (aka vertex coordinate)
				if (objFile.at(i).at(j) == ' ')
				{
					lineWords.push_back(word);
					word.clear();
				}
				//check if we're at the last character
				else if (j == objFile.at(i).size() - 1)
				{
					lineWords.push_back(word);
					word.clear();

					//extract face data and place into corresponding indices vectors
					for (size_t k = 0; k < lineWords.size(); k++)
					{
						//eg extraction from 1/2/3. Below val1 will now be = 1
						std::string face = lineWords.at(k);

						//extract kth vertex face
						int delimPos = face.find("/");
						std::string val1 = face.substr(0, delimPos);
						face.erase(0, delimPos + 1);

						//extract kth texCoord face
						delimPos = face.find("/");
						std::string val2 = face.substr(0, delimPos);
						face.erase(0, delimPos + 1);

						//remaining normal face
						std::string val3 = face;

						//convert to unsigned ints
						size_t vertFace = std::atoi(val1.c_str());
						size_t uvFace = std::atoi(val2.c_str());
						size_t normFace = std::atoi(val3.c_str());

						vertFace--;
						uvFace--;
						normFace--;

						//place into respective containers
						vertIndices.push_back(vertFace);
						uvIndices.push_back(uvFace);
						normIndices.push_back(normFace);
					}

					lineWords.clear();
				}
				//if no empty space, continue on storing data char by char
				else
					word.push_back(objFile.at(i).at(j));
			}
		}
	}
	
	return Mesh(vertices, textCoords, normals, vertIndices,uvIndices, normIndices);
}