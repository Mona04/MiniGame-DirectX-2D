#pragma once
#include "IResource.h"

enum class MeshType : uint
{
	Unknown,
	Quad,
	ScreenQuad,
	UIQuad,
	Custom
};

class Mesh final : public IResource
{
private:
	friend class ResourceManager;

private:
	Mesh(class Context* context);
	~Mesh() = default;

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	void SaveToFile(const std::string& path) override;
	void LoadFromFile(const std::string& path) override;

public:
	VertexBuffer* GetVertexBuffer() const { return vertexBuffer.get(); }
	IndexBuffer* GetIndexBuffer() const { return indexBuffer.get(); }
	const D3D11_PRIMITIVE_TOPOLOGY& GetTopology() const { return topology; }
	Geometry<VertexTextureNormal>& GetGeometry() { return geometry; }
	const MeshType& GetMeshType() const { return meshType; }

private:
	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& var) { topology = var; }
	void SetMeshType(const MeshType& var);
	void CreateBuffer();

private:
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	Geometry<VertexTextureNormal> geometry;
	MeshType meshType;
	D3D11_PRIMITIVE_TOPOLOGY topology;
};