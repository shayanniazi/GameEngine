#include "RenderingService.h"
#include "Mesh.h"
#include "glew.h"
#include <iostream>
#include "DisplayService.h"

Mat4 RenderingService::currentProjection;


void RenderingService::bindMesh(Mesh& mesh)
{
	//generate buffers and assign to mesh's buffer ID's
	glGenVertexArrays(1, &mesh.vaoID);
	glGenBuffers(1, &mesh.vboID);
	glGenBuffers(1, &mesh.iboID);

	//bind VAO before binding anything else
	glBindVertexArray(mesh.vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertexData.size(), &(mesh.vertexData[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.positionIndices.size() * sizeof(size_t), &(mesh.positionIndices[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
}

void RenderingService::unBindMesh(Mesh& mesh)
{
	glDeleteBuffers(1, &mesh.vaoID);
	glDeleteBuffers(1, &mesh.vboID);
	glDeleteBuffers(1, &mesh.iboID);

	std::cout << "Mesh unbound from GPU memory" << std::endl;
}

void RenderingService::drawMesh(const Mesh& mesh)
{
	glBindVertexArray(mesh.vaoID);
	glDrawElements(GL_TRIANGLES, mesh.positionIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void RenderingService::swapBuffers()
{
	SDL_GL_SwapWindow(DisplayService::getWindowHandle());
}

void RenderingService::clearBufferBits()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderingService::useWireframeMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
}

void RenderingService::useFillMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderingService::useOrthographicProjection()
{
	currentProjection = currentProjection.getOrthographic(DisplayService::leftClippingPlane, DisplayService::rightClippingPlane, 
													   	  DisplayService::bottomClippingPlane, DisplayService::topClippingPlane,
													   	  DisplayService::nearClippingPlane, DisplayService::farClippingPlane);
}

void RenderingService::usePerspectiveProjection()
{
	float aspectRatio = (float)DisplayService::screenWidth / (float)DisplayService::screenHeight;

	currentProjection = currentProjection.getProjection(DisplayService::FOV, aspectRatio, 
													    DisplayService::nearClippingPlane, DisplayService::farClippingPlane);
}

Mat4 RenderingService::getCurrentProjection()
{
	return currentProjection;
}