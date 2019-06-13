#include "ModelLoader.h"
#include "Mesh.h"
#include "Model.h"
#include "glew.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vertex.h"
#include "Utilities.h"
#include <iostream>
#include "RenderingService.h"
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

//loads generic model using ASSIMP library
std::shared_ptr<Model> ModelLoader::loadModel(const std::string& filePath)
{
	//read file
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	//error in reading file
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error in loading model file: " << filePath << ". Import error: " << import.GetErrorString() << std::endl;
		std::shared_ptr<Model> model(new Model());;
		return model;
	}

	std::string directory = filePath.substr(0, filePath.find_last_of('/'));

	//prepare output data
	std::vector<Mesh> meshes;

	//process and store meshes into meshes
	processNode(scene->mRootNode, scene, meshes);

	//The only unique storage for the loaded model, will be deleted once a renderComponent that binds to this model is destroyed by ComponentManager
	Model* model = new Model(meshes);
	
	//initialize and bind all meshes with drawing buffer data
	for (size_t i = 0; i < meshes.size(); i++)
		RenderingService::bindMesh(model->meshes.at(i));

	//output model now points to model resource which will be deleted only when the component containing a shared model ptr is destroyed
	std::shared_ptr<Model> outModel(model);;

	return outModel;
}

Mesh ModelLoader::processMesh(aiMesh *mesh, const aiScene *scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<size_t> indices;
	//std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		Vec3 vector; // we declare a placeholder vector 

		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.normal = vector;

		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			Vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.textureCoordinate = vec;
		}
		else
			vertex.textureCoordinate = Vec2(0.0f, 0.0f);
		
		//process tangents
		/*
		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		vertex.Tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		vertex.Bitangent = vector;
		*/
		//append all vertex data to vertex array
		vertices.push_back(vertex);

	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	//vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// 2. specular maps
	//vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// 3. normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// 4. height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices); //textures);
}

void ModelLoader::processNode(aiNode *node, const aiScene *scene, std::vector<Mesh>& meshes)
{
	// process each mesh located at the current node
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshes);
	}
}

//loads OBJ files (blender files)
std::shared_ptr<Model> ModelLoader::loadOBJ(const std::string& filePath)
{
	std::string file = Utilities::readFile(filePath);

	if (file == "")
	{
		std::cout << "Not able to load OBJ file: " << filePath << std::endl;
		std::shared_ptr<Model> model(new Model());;
		return model; 
	}

	//convert string to a string vector that contains line by line data
	std::vector<std::string> objFile;
	std::string line;

	for (size_t i = 0; i < file.size(); i++)
	{
		//if you encounter a '\n', append into line data
		if (file.at(i) == '\n')
		{
			line.push_back(file.at(i));

			objFile.push_back(line);
			line.clear();
		}
		//if at last line of file, since the last line doesn't have a '\n' character in it, we have to do this:
		else if (i == file.size() - 1)
		{
			line.push_back(file.at(i));

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
						word.push_back(objFile.at(i).at(j));

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
						word.push_back(objFile.at(i).at(j));

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
						word.push_back(objFile.at(i).at(j));

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
			//go through each line starting with 'f' but skip 'f' and corresponding empty space character ' '
			for (size_t j = 2; j < objFile.at(i).size(); j++)
			{
				//if empty space occurs in line, then store word (aka vertex coordinate)
				if (objFile.at(i).at(j) == ' ')
				{
					lineWords.push_back(word);
					word.clear();
				}
				//check if we're at the last character of the line containing 'f'
				else if (j == objFile.at(i).size() - 1)
				{
					word.push_back(objFile.at(i).at(j));

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

	std::vector<Vec3> indexedVertices;
	std::vector<Vec3> indexedNormals;
	std::vector<Vec2> indexedTexCoords;
	std::vector<Vertex> vertexData;

	size_t totalIndices = vertIndices.size(); //same will be for other vertex data like normals and textures will have the same # of indices

	//indexing vertex data (put data into format that openGL basically 'likes')
	for (size_t i = 0; i < totalIndices; i++)
	{
		//for positional data/coordinates
		size_t positionIndex = vertIndices.at(i);
		Vec3 position = vertices[positionIndex];
		indexedVertices.push_back(position);
		//overwrite ith index of indices buffer
		vertIndices.at(i) = i;

		//for normal coordinates and if model has normals
		if (!normIndices.empty())
		{
			size_t normalIndex = normIndices.at(0);
			Vec3 normal = normals[normalIndex];
			indexedNormals.push_back(normal);
			//overwrite ith index of indices buffer
			normIndices.at(i) = i;
		}

		//for texture coordinates and if model has text coords
		if (!uvIndices.empty())
		{
			size_t uvIndex = uvIndices.at(i);
			Vec2 textCoord = textCoords[uvIndex];
			indexedTexCoords.push_back(textCoord);
			//overwrite ith index of indices buffer
			uvIndices.at(i) = i;
		}

		//assign vertex data
		Vertex vertex;
		vertex.position = indexedVertices.at(i);
		vertex.normal = indexedNormals.at(i);
		vertex.textureCoordinate = indexedTexCoords.at(i);
		vertexData.push_back(vertex);
	}
	
	//create mesh with parsed vertex data
	Mesh mesh(vertexData, vertIndices, uvIndices, normIndices);

	//store mesh for output model
	std::vector<Mesh> meshes;
	meshes.push_back(mesh);

	//The only unique storage for the loaded model, will be deleted once a renderComponent that binds to this model is destroyed by ComponentManager
	Model* model = new Model(meshes);

	//initialize mesh with drawing buffer data
	RenderingService::bindMesh(model->meshes.front());

	//output model now points to model resource which will be deleted only when the component containing a shared model ptr is destroyed
	std::shared_ptr<Model> outModel(model);;

	return outModel;
}