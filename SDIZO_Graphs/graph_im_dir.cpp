#include "graph_im_dir.h"
#include "graph_exception.h"
#include <ostream>
#include <iostream>
#include <iomanip>

graph_im_dir::graph_im_dir(int v, int e) : a_graph_im(v, e)
{
}

void graph_im_dir::add_edge(int v_start, int v_end, int e_weight)
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
	inc_matrix_[v_end][curr_edges_] = new int{ -e_weight };

	curr_edges_++;
}

bool graph_im_dir::find_edge(int v_start, int v_end, int e_weight)
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
				&& *inc_matrix_[v_end][edge] == -e_weight)
			{
				return true;
			}
		}
	}
	return false;
}

bool graph_im_dir::has_edge(int v_start, int v_end)
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
			if (*inc_matrix_[v_start][edge] >= 0
				&& *inc_matrix_[v_end][edge] <= 0)
			{
				return true;
			}
		}
	}
	return false;
}

void graph_im_dir::print_graph()
{
	std::cout << "=== GRAF SKIEROWANY W REPREZENTACJI MACIERZY INCYDENCJI ===" << std::endl;
	a_graph_im::print_graph();
}

void graph_im_dir::spf_dijksra(int v_start, int v_end)
{
	//TODO
}

void graph_im_dir::spf_ford_bellman(int v_start, int v_end)
{
	//TODO
}
