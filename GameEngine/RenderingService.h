#pragma once
#include "Mat4.h"

class Mesh;

//STATIC CLASS
class RenderingService
{
public:
	static void bindMesh(Mesh& mesh);
	static void unBindMesh(Mesh& mesh);
	static void drawMesh(const Mesh& mesh);
	static void swapBuffers();
	static void useWireframeMode();
	static void useFillMode();
	static void clearBufferBits();
	static void useOrthographicProjection();
	static void usePerspectiveProjection();
	static Mat4 getCurrentProjection();
private:
	static Mat4 currentProjection;
};

