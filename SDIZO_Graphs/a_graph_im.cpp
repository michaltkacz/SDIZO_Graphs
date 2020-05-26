#include "a_graph_im.h"
#include <iostream>
#include <iomanip>
#include "graph_exception.h"
#include <stack>

a_graph_im::a_graph_im(int v, int e) : a_graph(v, e)
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

a_graph_im::~a_graph_im()
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

bool a_graph_im::is_connected()
{
	auto visited = new bool[v_] {false};
	int visited_counter = 0;
	std::stack<int> vertices;

	vertices.push(0);
	visited[0] = true;

	while (!vertices.empty())
	{
		int v = vertices.top();
		vertices.pop();
		visited_counter++;

		for (int edge = 0; edge < e_; edge++)
		{
			if (inc_matrix_[v][edge] != nullptr)
			{
				for (int u = 0; u < v_; u++)
				{
					if (u != v && inc_matrix_[u][edge] != nullptr)
					{
						if (!visited[u])
						{
							visited[u] = true;
							vertices.push(u);
						}
						break;
					}
				}
			}
		}
	}
	delete[] visited;

	return (visited_counter == v_);
}

void a_graph_im::print_graph()
{
	int last_edge_to_print = 0;
	int i = 0;
	int j = 0;

	while (last_edge_to_print != e_)
	{
		last_edge_to_print += 30;
		if (last_edge_to_print > e_)
		{
			last_edge_to_print = e_;
		}
		std::cout << "V\\E";
		for (i; i < last_edge_to_print; i++)
		{
			std::cout << std::setw(4) << i;
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
					std::cout << std::setw(4) << "n";
				}
				else
				{
					std::cout << std::setw(4) << *inc_matrix_[k][j];
				}

			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

