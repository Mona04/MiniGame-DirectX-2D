#include "Tree.h"

template<typename V, typename E>
inline Tree<V, E>::Tree()
	: tree(nullptr), nVertex(-1)
{
}

template<typename V, typename E>
inline Tree<V, E>::~Tree()
{
	Clear();
	SAFE_DELETE(tree);
}

template<typename V, typename E>
inline void Tree<V, E>::Init(std::vector<V>& a_vertex_property, const std::vector<E> a_edge_property, const std::vector<std::pair<int, int>>& a_edge)
{
	tree = new Graph(a_edge.begin()._Ptr, a_edge.end()._Ptr, a_edge_property.begin()._Ptr, a_vertex_property.size());
	for (int i = 0; i < a_vertex_property.size(); i++)
		(*tree)[i] = a_vertex_property[i];
	nVertex = a_vertex_property.size();
}

template<typename V, typename E>
inline void Tree<V, E>::Clear()
{
	if (tree) tree->clear();
}

template<typename V, typename E>
inline std::vector<V> Tree<V, E>::GetAdjacentDatas(const V& v_p)
{
	std::vector<V> result;
	int tmp = FindVertex(v_p);
	if (tmp != -1)
	{
		Vertex v = tmp;
		adjacency_iter ai, ai_end;
		for (boost::tie(ai, ai_end) = boost::adjacent_vertices(v, *tree); ai != ai_end; ai++)
		{
			result.emplace_back((*tree)[*ai]);
		}
	}
	return result;
}

template<typename V, typename E>
inline int Tree<V, E>::FindVertex(const V& v)
{
	for (int i = 0; i < nVertex; i++)
		if ((*tree)[i] == v)
			return i;

	return -1;
}
