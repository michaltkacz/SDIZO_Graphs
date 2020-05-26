#include "graph_im_indir.h"
#include "graph_exception.h"
#include <ostream>
#include <iostream>
#include <stack>

graph_im_indir::graph_im_indir(int v, int e) : a_graph_im(v, e)
{
}

void graph_im_indir::add_edge(int v_start, int v_end, int e_weight)
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

	inc_matrix_[v_start][curr_edges_] = new int{ e_weight };
	inc_matrix_[v_end][curr_edges_] = new int{ e_weight };

	curr_edges_++;
}

bool graph_im_indir::find_edge(int v_start, int v_end, int e_weight)
{
	if (!a_graph::find_edge(v_start, v_end, e_weight))
	{
		return false;
	}

	for (int edge = 0; edge < e_; edge++)
	{
		if (inc_matrix_[v_start][edge] != nullptr
			&& inc_matrix_[v_end][edge] != nullptr)
		{
			if (*inc_matrix_[v_start][edge] == e_weight
				&& *inc_matrix_[v_end][edge] == e_weight)
			{
				return true;
			}
		}
	}
	return false;
}

bool graph_im_indir::has_edge(int v_start, int v_end)
{
	if (!a_graph::has_edge(v_start, v_end))
	{
		return false;
	}

	for (int edge = 0; edge < e_; edge++)
	{
		if (inc_matrix_[v_start][edge] != nullptr
			&& inc_matrix_[v_end][edge] != nullptr)
		{
			return true;
		}
	}
	return false;
}

void graph_im_indir::print_graph()
{
	std::cout << "=== GRAF NIESKIEROWANY W REPREZENTACJI MACIERZY INCYDENCJI ===" << std::endl;
	a_graph_im::print_graph();
}

void graph_im_indir::mst_prim(int v_start)
{
	//TODO
}

void graph_im_indir::mst_kruskal(int v_start)
{
	//TODO
}
