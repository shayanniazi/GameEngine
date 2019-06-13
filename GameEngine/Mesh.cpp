#include "Mesh.h"
#include "Vec3.h"
#include "Vec2.h"
#include <iostream>
#include "RenderingService.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const std::vector<Vertex>& vertexData, const  std::vector<size_t>& positionIndices,
	       const std::vector<size_t>& uvIndices, const std::vector<size_t>& normalIndices)
{
	this->vertexData = vertexData;
	this->positionIndices = positionIndices;
	this->uvIndices = uvIndices;
	this->normalIndices = normalIndices;
}

Mesh::Mesh(const std::vector<Vertex>& vertexData, const std::vector<size_t>& positionIndices)
{
	this->vertexData = vertexData;
	this->positionIndices = positionIndices;
}

Mesh::~Mesh()
{
	//if mesh is not from a copy destructor and has a valid VAO ID. 
	//Usually mesh is destroyed when a renderComponent is removed from component database. 
	//Since each renderComponent stores a unique model (and the model contains the meshes)
	if (vaoID != 0 && vboID != 0 && iboID != 0)
	{
		RenderingService::unBindMesh(*this);
	}
}

void Mesh::operator=(const Mesh& mesh)
{
	this->vertexData = mesh.vertexData;
	this->positionIndices = mesh.positionIndices;
	this->uvIndices = mesh.uvIndices;
	this->normalIndices = mesh.normalIndices;
}

size_t Mesh::getVaoID()
{
	return vaoID;
}

size_t Mesh::getVboID()
{
	return vboID;
}

size_t Mesh::getIboID()
{
	return iboID;
}