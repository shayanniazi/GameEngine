#pragma once
#include <vector>
#include "Vertex.h"

class Vec3;
class Vec2;

class Mesh
{
public:
	std::vector<Vertex> vertexData;
	std::vector<size_t> positionIndices;
	std::vector<size_t> uvIndices;
	std::vector<size_t> normalIndices;

	Mesh();

	Mesh(const std::vector<Vertex>& vertexData, 
		 const  std::vector<size_t>& positionIndices, 
		 const std::vector<size_t>& uvIndices, 
		 const std::vector<size_t>& normalIndices);

	Mesh(const std::vector<Vertex>& vertexData, const std::vector<size_t>& positionIndices);

	~Mesh();
	
	void operator = (const Mesh& mesh);

	size_t getVboID();
	size_t getIboID();
	size_t getVaoID();

private:
	friend class RenderingService;

	size_t vboID = 0;
	size_t iboID = 0;
	size_t vaoID = 0;
};