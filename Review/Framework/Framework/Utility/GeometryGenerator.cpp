#include "Framework.h"
#include "GeometryGenerator.h"

void GeometryGenerator::CreateQuad(Geometry<VertexTextureNormal>* geometry)
{
	geometry->AddVertex(VertexTextureNormal({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ -0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ +0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ +0.5f, +0.5f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));

	geometry->AddIndex(0); geometry->AddIndex(1); geometry->AddIndex(2);
	geometry->AddIndex(2); geometry->AddIndex(1); geometry->AddIndex(3);
}

void GeometryGenerator::CreateScreenQuad(Geometry<struct VertexTextureNormal>* geometry, float width, float height)
{
	geometry->AddVertex(VertexTextureNormal({ -width / 2.0f, -height / 2.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ -width / 2.0f, +height / 2.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ +width / 2.0f, -height / 2.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ +width / 2.0f, +height / 2.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));

	geometry->AddIndex(0); geometry->AddIndex(1); geometry->AddIndex(2);
	geometry->AddIndex(2); geometry->AddIndex(1); geometry->AddIndex(3);
}

void GeometryGenerator::CreateUIQuad(Geometry<struct VertexTextureNormal>* geometry)
{
	geometry->AddVertex(VertexTextureNormal({ 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
	geometry->AddVertex(VertexTextureNormal({ 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));

	geometry->AddIndex(0); geometry->AddIndex(1); geometry->AddIndex(2);
	geometry->AddIndex(2); geometry->AddIndex(1); geometry->AddIndex(3);
}

void GeometryGenerator::CreateCircle(Geometry<struct VertexTextureNormal>* geometry)
{
	//chrono, 
	//timeGetTime(), GetTickCount(), Queryperformance(),
}
