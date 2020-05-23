#include "graph_al.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>


graph_al::graph_al(int v, int e) : a_graph(v, e)
{
	adj_list_ = new adj_list_el*[v_];

	for(int i=0; i<v_; i++)
	{
		adj_list_[i] = nullptr;
	}
}

graph_al::~graph_al()
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

void graph_al::add_edge(int v_start, int v_end, int e_weight)
{
	try
	{
		a_graph::add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}

	if (find_edge(v_start, v_end, e_weight))
	{
		throw graph_exception("Ta krawedz juz istnieje");
	}

	auto new_list_el = new adj_list_el{ v_end, e_weight, adj_list_[v_start] };
	adj_list_[v_start] = new_list_el;
	curr_edges_++;
}

bool graph_al::find_edge(int v_start, int v_end, int e_weight)
{
	if (!a_graph::find_edge(v_start, v_end, e_weight))
	{
		return false;
	}

	auto v_list = adj_list_[v_start];
	while(v_list)
	{
		if(v_list->v_end == v_end && v_list->weight == e_weight)
		{
			return true;
		}
		v_list = v_list->next;
	}

	return false;
}

void graph_al::print_graph()
{
	for (int i = 0; i < v_; i++)
	{
		std::cout << "V[" << std::setw(3) << i << "] = ";
		auto v_list = adj_list_[i];
		while (v_list)
		{
			std::cout << "[";
			std::cout << std::setw(3) << v_list->v_end;
			std::cout << ",";
			std::cout << std::setw(3) << v_list->weight;
			std::cout << "]";
			v_list = v_list->next;
		}
		std::cout << std::endl;
	}
}
