#include "graph_al_dir.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>
#include <stack>

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
	//dziala ?????????????????????????????????????????????? bo w sumie to nie wiem
	// NIE DZIALA, POPRAWIC
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

		auto neighbour = adj_list_[v];
		while (neighbour)
		{
			int u = neighbour->v_end;
			if (!visited[u])
			{
				visited[u] = true;
				vertices.push(u);
			}
			neighbour = neighbour->next;
		}
	}
	delete[] visited;

	return (visited_counter == v_);
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
