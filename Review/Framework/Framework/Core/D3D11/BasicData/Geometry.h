#pragma once
#include "Framework.h"

template <class T>
class Geometry final
{
public:
	Geometry() = default;
	~Geometry() = default;

	Geometry(const Geometry&) = delete;
	Geometry& operator=(const Geometry&) = delete;
	Geometry(Geometry&&) = delete;

	const uint GetVertexCount() const { return vertices.size(); }
	const uint GetIndexCount() const { return indices.size(); }
	void Clear();

	//============================================
	//Vertex
	std::vector<T>& GetVertices() { return vertices; }
	void GetVertices
	(
		const uint& offset,
		const uint& count,
		std::vector<T>& vertices
	);
	T* GetVertexData() { return vertices.data(); }

	void AddVertex(const T& vertex);
	void AddVertices(const std::vector<T>& vertices);
	void SetVertices(const std::vector<T>& vertices);
	//============================================

	//============================================
	//Index
	const std::vector<uint>& GetIndices() const { return indices; }
	void GetIndices
	(
		const uint& offset,
		const uint& count,
		std::vector<uint>& indices
	);
	uint* GetIndexData() { return indices.data(); }

	void AddIndex(const uint& index);
	void AddIndices(const std::vector<uint>& indices);
	void SetIndices(const std::vector<uint>& indices);
	//============================================

private:
	std::vector<T> vertices;
	std::vector<uint> indices;
};
#include "Geometry.inl"