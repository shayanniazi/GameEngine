#include "RenderingSystem.h"
#include "ComponentDatabase.h"
#include "ShaderService.h"
#include "RenderingService.h"
#include "RenderComponent.h"
#include "Mat4.h"
#include "ECSEntity.h"
#include "TransformComponent.h"
#include "DisplayService.h"
#include "Camera.h"

void RenderingSystem::draw()
{
	
	std::vector<RenderComponent> renderComponents = ComponentDatabase::getAllComponents<RenderComponent>();

	//loop through each renderComponent
	for (size_t i = 0; i < renderComponents.size(); i++)
	{
		TransformComponent* transform = renderComponents.at(i).getOwner()->getComponent<TransformComponent>();

		//loop through each mesh for each model inside renderComponents
		for (size_t j = 0; j < renderComponents.at(i).model.get()->meshes.size(); j++)
		{
			//if entity has valid transform, then apply transformations
			if (transform != nullptr)
			{
				Mat4 modelMatrix = modelMatrix.getModel(*transform);
				
				Mat4 projMatrix = RenderingService::getCurrentProjection();
				
				Mat4 viewMatrix = viewMatrix.getView(*Camera::activeCamera);

				Mat4 MVP = projMatrix * viewMatrix * modelMatrix;

				size_t MVPLoc = glGetUniformLocation(ShaderService::getActiveShaderProgram(), "MVP");
				glUniformMatrix4fv(MVPLoc, 1, GL_TRUE, &MVP.matrix4x4[0][0]);
			}

			RenderingService::drawMesh(renderComponents.at(i).model.get()->meshes.at(j));
		}
	}
}

void RenderingSystem::update()
{

}