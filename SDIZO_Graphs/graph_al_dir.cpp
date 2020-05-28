#include "graph_al_dir.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include "graph_al_indir.h"

graph_al_dir::graph_al_dir(int v, int e) : a_graph_al(v, e)
{
}

void graph_al_dir::add_edge(int v_start, int v_end, int e_weight)
{
	try
	{
		a_graph_al::add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}

	auto new_list_el = new adj_list_el{ v_end, e_weight, adj_list_[v_start] };
	adj_list_[v_start] = new_list_el;
	curr_edges_++;
}

bool graph_al_dir::is_connected()
{
	auto g_indir = new graph_al_indir(v_, e_);

	for(int i=0; i< v_; i++)
	{
		auto ls = adj_list_[i];
		while(ls)
		{
			int v_start = i;
			int v_end = ls->v_end;
			int e_weight = ls->weight;

			if (!g_indir->has_edge(v_start, v_end))
			{
				g_indir->add_edge(v_start, v_end, e_weight);
			}
			ls = ls->next;
		}	
	}

	bool is_connected = g_indir->is_connected();
	delete g_indir;
	return is_connected;
}

void graph_al_dir::print_graph()
{
	std::cout << "=== GRAF SKIEROWANY W REPREZENTACJI LISTY SASIEDZTWA ===" << std::endl;
	a_graph_al::print_graph();
}

void graph_al_dir::spf_dijksra(int v_start, int v_end)
{
	//TODO
}

void graph_al_dir::spf_ford_bellman(int v_start, int v_end)
{
	//TODO
}
