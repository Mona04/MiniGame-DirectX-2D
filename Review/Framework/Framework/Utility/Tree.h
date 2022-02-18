#pragma once
#include "Framework.h"

template<typename V>
class Tree
{
public:
	Tree();
	~Tree();

	void Init(std::vector<V>& vertex_property, const std::vector<std::pair<int, int>>& edges);
	void Clear();

	std::vector<V> GetAdjacentDatas(const V& v);
	int FindVertex(const V& v);

private:
	std::vector<V> nodes;
	std::unordered_map<int, std::vector<int>> edges;
};


#include "Tree.inl"