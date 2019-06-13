#include "Model.h"
#include "Mesh.h"

Model::Model(){}
Model::~Model(){}

Model::Model(std::vector<Mesh> meshes)
{
	this->meshes = meshes;
}

void Model::operator=(const Model& model)
{
	this->meshes = model.meshes;
}