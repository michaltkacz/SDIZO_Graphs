#include "a_graph_al.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>
#include <queue>


a_graph_al::a_graph_al(int v, int e) : a_graph(v, e)
{
	adj_list_ = new adj_list_el*[v_];

	for(int i=0; i<v_; i++)
	{
		adj_list_[i] = nullptr;
	}
}

a_graph_al::~a_graph_al()
{
	for (int i = 0; i < v_; i++)
	{
		auto v_list = adj_list_[i];
		while (v_list)
		{
			auto temp = v_list;
			v_list = v_list->next;
			delete temp;
		}
	}

	delete[] adj_list_;
	adj_list_ = nullptr;
}

void a_graph_al::add_edge(int v_start, int v_end, int e_weight)
{
	try
	{
		a_graph::add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}

	if (has_edge(v_start, v_end))
	{
		throw graph_exception("Krawedz miedzy tymi wierzcholkami juz istnieje");
	}
}

bool a_graph_al::find_edge(int v_start, int v_end, int e_weight)
{
	if (!a_graph::find_edge(v_start, v_end, e_weight))
	{
		return false;
	}

	auto v_list = adj_list_[v_start];
	while (v_list)
	{
		if (v_list->v_end == v_end && v_list->weight == e_weight)
		{
			return true;
		}
		v_list = v_list->next;
	}

	return false;
}

bool a_graph_al::has_edge(int v_start, int v_end)
{
	if (!a_graph::has_edge(v_start, v_end))
	{
		return false;
	}

	auto v_list = adj_list_[v_start];
	while (v_list)
	{
		if (v_list->v_end == v_end)
		{
			return true;
		}
		v_list = v_list->next;
	}

	return false;
}

void a_graph_al::print_graph()
{
	const int max_el_to_display = 10;
	for (int i = 0; i < v_; i++)
	{
		std::cout << "V[" << std::setw(3) << i << "] = ";
		auto v_list = adj_list_[i];

		int counter = 1;
		while (v_list)
		{
			if(counter % max_el_to_display == 0)
			{
				std::cout << std::endl;
				std::cout << "         ";
			}
			counter++;

			std::cout << "[";
			std::cout << std::setw(3) << v_list->v_end;
			std::cout << ",";
			std::cout << std::setw(3) << v_list->weight;
			std::cout << "]";
			v_list = v_list->next;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//a_graph* a_graph_al::mst_prim(int v_start)
//{
//	using namespace std;
//	const int NIL = -1;
//	auto key = new int[v_];
//	auto p = new int[v_];
//	auto in_mst = new bool[v_];
//	for(int i=0; i<v_; i++)
//	{
//		key[i] = INT_MAX;
//		p[i] = NIL;
//		in_mst[i] = false;
//	}
//
//	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//	key[v_start] = 0;
//	pq.push(make_pair(key[v_start], v_start));
//
//	while(!pq.empty())
//	{
//		int u = pq.top().second;
//		pq.pop();
//		in_mst[u] = true;
//
//		auto adj_v = adj_list_[u];
//		while(adj_v)
//		{
//			int v_end = adj_v->v_end;
//			int weight = adj_v->weight;
//
//			if(in_mst[v_end] && weight < key[v_end])
//			{
//				key[v_end] = weight;
//				p[v_end] = u;
//				pq.push(make_pair(key[v_end], v_end));
//			}
//		}
//	}
//
//	for(int i=0; i< v_; i++)
//	{
//		std::cout << p[i] << " - " << i << std::endl;
//	}
//
//	delete[] key;
//	delete[] p;
//	delete[] in_mst;
//	return nullptr;
//}
