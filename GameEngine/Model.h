#pragma once
#include <vector>
#include "Mesh.h"

class Model
{
public:
	Model();
	Model(std::vector<Mesh> meshes);
	~Model();

	void operator = (const Model& model);
	std::vector<Mesh> meshes;
};

