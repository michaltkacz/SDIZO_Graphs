#include "graph_im.h"
#include <iostream>
#include <iomanip>
#include "graph_exception.h"

graph_im::graph_im(int v, int e) : a_graph(v, e)
{
	inc_matrix_ = new int**[v_];
	for(int i=0; i<v_; i++)
	{
		inc_matrix_[i] = new int*[e_];
	}

	for(int i=0; i<v_; ++i)
	{
		for(int j=0; j<e_; ++j)
		{
			inc_matrix_[i][j] = nullptr;
		}
	}
	curr_edges_ = 0;
}

graph_im::~graph_im()
{
	for (int i = 0; i < v_; i++)
	{
		for (int j = 0; j < e_; j++)
		{
			delete inc_matrix_[i][j];
		}
		delete[] inc_matrix_[i];
	}
	delete[] inc_matrix_;
	inc_matrix_ = nullptr;
}

void graph_im::add_edge(int v_start, int v_end, int e_weight)
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

	inc_matrix_[v_start][curr_edges_] = new int{e_weight};
	inc_matrix_[v_end][curr_edges_] = new int{-e_weight};

	curr_edges_++;
}

bool graph_im::find_edge(int v_start, int v_end, int e_weight)
{
	if(!a_graph::find_edge(v_start, v_end, e_weight))
	{
		return false;
	}

	for(int edge = 0; edge<e_; edge++)
	{
		if (inc_matrix_[v_start][edge] != nullptr
			&& inc_matrix_[v_end][edge] != nullptr )
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

void graph_im::print_graph()
{
	std::cout << "=== GRAF W REPREZENTACJI MACIERZY INCYDENCJI ===" << std::endl;
	int last_edge_to_print = 0;
	int i = 0;
	int j = 0;

	while(last_edge_to_print != e_)
	{
		last_edge_to_print += 40;
		if (last_edge_to_print > e_)
		{
			last_edge_to_print = e_;
		}
		std::cout << "V\\E";
		for (i; i < last_edge_to_print; i++)
		{
			std::cout << std::setw(3) << i;
		}
		std::cout << std::endl;

		int l = j;
		for (int k = 0; k < v_; k++)
		{
			std::cout << std::setw(3) << k;
			
			for (j = l; j < i; j++)
			{
				if (inc_matrix_[k][j] == nullptr)
				{
					std::cout << std::setw(3) << "n";
				}
				else
				{
					std::cout << std::setw(3) << *inc_matrix_[k][j];
				}

			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

}

