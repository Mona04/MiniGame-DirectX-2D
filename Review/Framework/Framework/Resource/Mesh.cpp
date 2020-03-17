#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Context * context)
	: IResource(context)
	, topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, meshType(MeshType::Unknown)
{
	vertexBuffer = std::make_shared<VertexBuffer>(context);
	indexBuffer = std::make_shared<IndexBuffer>(context);
}

void Mesh::LoadFromFile(const std::string& path)
{   
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		meshType = static_cast<MeshType>(stream.ReadUInt());
		topology = static_cast<D3D11_PRIMITIVE_TOPOLOGY>(stream.ReadUInt());
	}
	stream.Close();
	
	CreateBuffer();
}

void Mesh::SaveToFile(const std::string & path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(static_cast<uint>(meshType));
		stream.Write(static_cast<uint>(topology));
	}
	stream.Close();
}

void Mesh::SetMeshType(const MeshType & var)
{
	if (meshType == var)
		return;

	meshType = var;
	
	CreateBuffer();
}

void Mesh::CreateBuffer()
{
	vertexBuffer->Clear();
	indexBuffer->Clear();

	switch (meshType)
	{
	case MeshType::Unknown:
		break;
	case MeshType::Quad:
		geometry.Clear();
		GeometryGenerator::CreateQuad(&geometry);
		break;
	case MeshType::ScreenQuad:
		geometry.Clear();
		GeometryGenerator::CreateScreenQuad(&geometry);
		break;
	case MeshType::UIQuad:
		geometry.Clear();
		GeometryGenerator::CreateUIQuad(&geometry);
		break;
	case MeshType::Custom:
		break;
	}

	vertexBuffer->Create(geometry.GetVertices());
	indexBuffer->Create(geometry.GetIndices());
}
