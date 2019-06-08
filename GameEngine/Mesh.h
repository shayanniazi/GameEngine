#pragma once
#include <vector>

class Vec3;
class Vec2;

struct Indices
{
	std::vector<Vec3> positionIndices;
	std::vector<Vec3> uvIndices;
	std::vector<Vec3> normalIndices;
};

class Mesh
{
public:
	std::vector<Vec3> positionVertices;
	std::vector<Vec2> textureVertices;
	std::vector<Vec3> normalVertices;
	std::vector<size_t> positionIndices;
	std::vector<size_t> uvIndices;
	std::vector<size_t> normalIndices;

	Mesh();
	Mesh(std::vector<Vec3> positionVertices, std::vector<Vec2> textureVertices, std::vector<Vec3> normalVertices,
		 std::vector<size_t> positionIndices, std::vector<size_t> uvIndices, std::vector<size_t> normalIndices);
	Mesh(const Mesh& mesh);
	~Mesh();
	void operator = (const Mesh& mesh);
};