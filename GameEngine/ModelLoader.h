#pragma once
#include <string>
#include <memory>
#include <vector>
#include "scene.h"

class Model;
class Mesh;

//STATIC CLASS
class ModelLoader
{
public:
	static std::shared_ptr<Model> loadOBJ(const std::string& filePath);
	static std::shared_ptr<Model> loadModel(const std::string& filePath);
private:
	static void processNode(aiNode *node, const aiScene *scene, std::vector<Mesh>& meshes);
	static Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

