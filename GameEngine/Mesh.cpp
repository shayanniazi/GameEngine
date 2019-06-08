#include "Mesh.h"
#include "Vec3.h"
#include "Vec2.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vec3> positionVertices, std::vector<Vec2> textureVertices, std::vector<Vec3> normalVertices,
	std::vector<size_t> positionIndices, std::vector<size_t> uvIndices, std::vector<size_t> normalIndices)
{
	this->positionVertices = positionVertices;
	this->textureVertices = textureVertices;
	this->normalVertices = normalVertices;
	this->positionIndices = positionIndices;
	this->uvIndices = uvIndices;
	this->normalIndices = normalIndices;
}

Mesh::Mesh(const Mesh& mesh)
{
	this->positionVertices = positionVertices;
	this->textureVertices = textureVertices;
	this->normalVertices = normalVertices;
	this->positionIndices = mesh.positionIndices;
	this->uvIndices = mesh.uvIndices;
	this->normalIndices = mesh.normalIndices;
}

Mesh::~Mesh()
{
}

void Mesh::operator=(const Mesh& mesh)
{
	this->positionVertices = positionVertices;
	this->textureVertices = textureVertices;
	this->normalVertices = normalVertices;
	this->positionIndices = mesh.positionIndices;
	this->uvIndices = mesh.uvIndices;
	this->normalIndices = mesh.normalIndices;
}
