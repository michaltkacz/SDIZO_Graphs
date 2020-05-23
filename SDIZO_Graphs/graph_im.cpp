#include "graph_im.h"
#include <iostream>
#include <iomanip>
#include "graph_exception.h"

graph_im::graph_im(int v, int e) : a_graph(v, e)
{
	inc_matrix_ = new matrix_cell_**[v_];
	for(int i=0; i<v_; i++)
	{
		inc_matrix_[i] = new matrix_cell_*[e_];
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

	inc_matrix_[v_start][curr_edges_] = new matrix_cell_{ e_weight, START };
	inc_matrix_[v_end][curr_edges_] = new matrix_cell_{ e_weight, END };

	curr_edges_++;
}

bool graph_im::find_edge(int v_start, int v_end, int e_weight)
{
	if(!a_graph::find_edge(v_start, v_end, e_weight))
	{
		return false;
	}

	// WTF
	for(int edge = 0; edge<e_; edge++)
	{
		if (inc_matrix_[v_start][edge] != nullptr
			&& inc_matrix_[v_end][edge] != nullptr )
		{
			if (inc_matrix_[v_start][edge]->dir == START
				&& inc_matrix_[v_end][edge]->dir == END)
			{
				if (inc_matrix_[v_start][edge]->weight == e_weight
					&& inc_matrix_[v_end][edge]->weight == e_weight)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void graph_im::print_graph()
{
	std::cout << "=== GRAF W REPREZENTACJI MACIERZY INCYDENCJI ===" << std::endl;
	std::cout << "  ~";
	for (int i = 0; i < e_; i++) 
	{
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl;
	for (int i = 0; i < v_; i++)
	{
		std::cout << std::setw(3) << i;
		for (int j = 0; j < e_; j++)
		{
			if(inc_matrix_[i][j] == nullptr)
			{
				std::cout << std::setw(3) << "N";
			}else if (inc_matrix_[i][j]->dir == START)
			{
				std::cout << std::setw(3) << -1 * inc_matrix_[i][j]->weight;
			}else
			{
				std::cout << std::setw(3) << inc_matrix_[i][j]->weight;
			}
			
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

