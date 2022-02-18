#include "Tree.h"

template<typename V>
inline Tree<V>::Tree()
{
}

template<typename V>
inline Tree<V>::~Tree()
{
	Clear();
}

template<typename V>
void Tree<V>::Init(std::vector<V>& in_nodes, const std::vector<std::pair<int, int>>& in_edges)
{
	Clear();

	nodes = in_nodes;
	for (const std::pair<int, int>& e : in_edges)
		edges[e.first].push_back(e.second);
}

template<typename V>
void Tree<V>::Clear()
{
	nodes.clear(); nodes.shrink_to_fit();
	edges.clear();
}

template<typename V>
std::vector<V> Tree<V>::GetAdjacentDatas(const V& v_p)
{
	std::vector<V> result;
	int tmp = FindVertex(v_p);
	if (tmp != -1)
	{
		for (int idx : edges[tmp])
			result.push_back(nodes[idx]);
	}
	return result;
}

template<typename V>
inline int Tree<V>::FindVertex(const V& v)
{
	for (int i = 0; i < (int)nodes.size(); i++)
		if (nodes[i] == v)
			return i;

	return -1;
}
