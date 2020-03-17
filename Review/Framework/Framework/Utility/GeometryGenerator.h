#pragma once

template <typename T> class Geometry;

class GeometryGenerator final
{
public:
	static void CreateQuad(Geometry<struct VertexTextureNormal>* geometry);
	static void CreateScreenQuad(Geometry<struct VertexTextureNormal>* geometry, float width = 2.0f, float height = 2.0f);
	static void CreateUIQuad(Geometry<struct VertexTextureNormal>* geometry);
	static void CreateCircle(Geometry<struct VertexTextureNormal>* geometry);
};