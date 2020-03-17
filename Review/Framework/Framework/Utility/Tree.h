#pragma once
#include "Framework.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

template<typename V, typename E>
class Tree
{
private:
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, V, E> Graph;
	typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef typename boost::graph_traits<Graph>::vertex_iterator vertex_iter;
	typedef typename boost::graph_traits<Graph>::adjacency_iterator adjacency_iter;

public:
	Tree();
	~Tree();

	void Init(std::vector<V>& a_vertex_property, const std::vector<E> a_edge_property, const std::vector<std::pair<int, int>>& a_edge);
	void Clear();

	std::vector<V> GetAdjacentDatas(const V& v);
	int FindVertex(const V& v);

	Graph* GetTree() { return tree; }

private:
	Graph* tree;
	int nVertex;
};


#include "Tree.inl"