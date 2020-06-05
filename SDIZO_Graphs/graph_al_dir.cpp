#include "graph_al_dir.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include "graph_al_indir.h"
#include <queue>

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

void graph_al_dir::spf_dijksra(int v_start, int v_end, bool test_performance)
{
	if(!a_graph::check_vertex_good(v_start))
	{
		throw graph_exception("Wierzcholek poczatkowy nie istnieje");
	}

	if(!a_graph::check_vertex_good(v_end) && v_end != -1)
	{
		throw graph_exception("Wierzcholek koncowy nie istnieje");
	}

	const int NIL = -1;
	const int INF = 1000000;
	auto d = new int[v_];
	auto p = new int[v_];
	auto qs = new bool[v_];
	for(int i=0; i<v_; i++)
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

		auto adj_v = adj_list_[u];
		while (adj_v)
		{
			if (!qs[adj_v->v_end] && (d[adj_v->v_end] > d[u] + adj_v->weight))
			{
				d[adj_v->v_end] = d[u] + adj_v->weight;
				p[adj_v->v_end] = u;
			}
			adj_v = adj_v->next;
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
	delete[] qs;
}

void graph_al_dir::spf_ford_bellman(int v_start, int v_end, bool test_performance)
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

	for(int i=0; i<v_; i++)
	{
		for(int j=0; j<v_; j++)
		{
			auto adj_v = adj_list_[j];
			while (adj_v)
			{
				if (d[adj_v->v_end] > d[j] + adj_v->weight)
				{
					d[adj_v->v_end] = d[j] + adj_v->weight;
					p[adj_v->v_end] = j;
				}
				adj_v = adj_v->next;
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
