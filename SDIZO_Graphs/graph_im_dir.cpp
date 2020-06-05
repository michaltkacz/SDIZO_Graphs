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

void graph_im_dir::spf_dijksra(int v_start, int v_end, bool test_performance)
{
	if (!a_graph::check_vertex_good(v_start))
	{
		throw graph_exception("Wierzcholek poczatkowy nie istnieje");
	}

	if (!a_graph::check_vertex_good(v_end) && v_end != -1)
	{
		throw graph_exception("Wierzcholek koncowy nie istnieje");
	}

	const int NIL = -1;
	const int INF = 1000000;
	auto d = new int[v_];
	auto p = new int[v_];
	auto qs = new bool[v_];
	for (int i = 0; i < v_; i++)
	{
		d[i] = INF;
		p[i] = NIL;
		qs[i] = false;
	}
	d[v_start] = 0;

	int j = 0;
	int u = 0;
	for (int i = 0; i < v_; i++)
	{

		for (j = 0; qs[j]; j++);
		for (u = j++; j < v_; j++)
		{
			if (!qs[j] && (d[j] < d[u]))
			{
				u = j;
			}
		}

		qs[u] = true;

		// O__O
		for (int x = 0; x < e_; x++)
		{
			if (inc_matrix_[u][x] != nullptr)
			{
				if (*inc_matrix_[u][x] >= 0)
				{
					for (int y = 0; y < v_; y++)
					{
						if (y != u && inc_matrix_[y][x] != nullptr)
						{
							if (*inc_matrix_[y][x] <= 0)
							{
								if (!qs[y] && (d[y] > d[u] + *inc_matrix_[u][x]))
								{
									d[y] = d[u] + *inc_matrix_[u][x];
									p[y] = u;
									break;
								}
							}
						}
					}
				}
			}
		}
	}


	if (!test_performance)
	{
		if (v_end == -1)
		{
			std::cout << "Droga SPF(v start - v end: d)" << std::endl;
			for (int i = 0; i < v_; i++)
			{
				std::cout << std::setw(3) << v_start;
				std::cout << " - ";
				std::cout << std::setw(3) << i;
				std::cout << " : ";
				if (d[i] == INF)
				{
					std::cout << std::setw(5) << "-" << std::endl;
				}
				else
				{
					std::cout << std::setw(5) << d[i] << std::endl;
				}
			}
		}
		else
		{
			std::cout << "Droga z wierzcholka " << v_start;
			std::cout << " do wierzcholka " << v_end;
			std::cout << " wynosi: ";
			if (d[v_end] == INF)
			{
				std::cout << "-" << std::endl;
			}
			else
			{
				std::cout << d[v_end] << std::endl;
			}
		}
	}

	delete[] d;
	delete[] p;
	delete[] qs;
}

void graph_im_dir::spf_ford_bellman(int v_start, int v_end, bool test_performance)
{
	if (!a_graph::check_vertex_good(v_start))
	{
		throw graph_exception("Wierzcholek poczatkowy nie istnieje");
	}

	if (!a_graph::check_vertex_good(v_end) && v_end != -1)
	{
		throw graph_exception("Wierzcholek koncowy nie istnieje");
	}


	const int NIL = -1;
	const int INF = 1000000;
	auto d = new int[v_];
	auto p = new int[v_];
	for (int i = 0; i < v_; i++)
	{
		d[i] = INF;
		p[i] = NIL;
	}
	d[v_start] = 0;

	for (int i=0; i<v_; i++)
	{
		for(int x=0; x<v_; x++)
		{
			for (int j=0; j<e_; j++)
			{
				if (inc_matrix_[x][j] != nullptr)
				{
					if (*inc_matrix_[x][j] >= 0)
					{
						for (int y=0; y<v_; y++)
						{
							if (y != i && inc_matrix_[y][j] != nullptr)
							{
								if (*inc_matrix_[y][j] <= 0)
								{
									if (d[y] > d[x] + *inc_matrix_[x][j])
									{
										d[y] = d[x] + *inc_matrix_[x][j];
										p[y] = x;
										break;
									}
								}
							}
						}
					}
				}
			}	
		}
	}


	if (!test_performance)
	{
		if (v_end == -1)
		{
			std::cout << "Droga SPF(v start - v end: d)" << std::endl;
			for (int i = 0; i < v_; i++)
			{
				std::cout << std::setw(3) << v_start;
				std::cout << " - ";
				std::cout << std::setw(3) << i;
				std::cout << " : ";
				if (d[i] == INF)
				{
					std::cout << std::setw(3) << "-" << std::endl;
				}
				else
				{
					std::cout << std::setw(3) << d[i] << std::endl;
				}
			}
		}
		else
		{
			std::cout << "Droga z wierzcholka " << v_start;
			std::cout << " do wierzcholka " << v_end;
			std::cout << " wynosi: ";
			if (d[v_end] == INF)
			{
				std::cout << "-" << std::endl;
			}
			else
			{
				std::cout << d[v_end] << std::endl;
			}
		}
	}

	delete[] d;
	delete[] p;
}
