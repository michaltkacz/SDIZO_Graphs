#include "graph_al_indir.h"
#include "graph_exception.h"
#include <ostream>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>
#include <algorithm>


graph_al_indir::graph_al_indir(int v, int e) : a_graph_al(v, e)
{
}

void graph_al_indir::add_edge(int v_start, int v_end, int e_weight)
{
	try
	{
		a_graph_al::add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}

	auto new_list_el1 = new adj_list_el{ v_end, e_weight, adj_list_[v_start] };
	adj_list_[v_start] = new_list_el1;

	auto new_list_el2 = new adj_list_el{ v_start, e_weight, adj_list_[v_end] };
	adj_list_[v_end] = new_list_el2;

	curr_edges_++;
}

bool graph_al_indir::is_connected()
{
	auto visited = new bool[v_] {false};
	int visited_counter = 0;
	std::stack<int> vertices;

	vertices.push(0);
	visited[0] = true;

	while(!vertices.empty())
	{
		int v = vertices.top();
		vertices.pop();
		visited_counter++;

		auto neighbour = adj_list_[v];
		while(neighbour)
		{
			int u = neighbour->v_end;
			if(!visited[u])
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

void graph_al_indir::print_graph()
{
	std::cout << "=== GRAF NIESKIEROWANY W REPREZENTACJI LISTY SASIEDZTWA ===" << std::endl;
	a_graph_al::print_graph();
}

void graph_al_indir::mst_prim()
{
	using namespace std;
	const int NIL = -1;
	int v_start = 0;
	auto key = new int[v_];
	auto p = new int[v_];
	auto in_mst = new bool[v_];
	for(int i=0; i<v_; i++)
	{
		key[i] = INT_MAX;
		p[i] = NIL;
		in_mst[i] = false;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	key[v_start] = 0;
	pq.push(make_pair(key[v_start], v_start));

	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		in_mst[u] = true;

		auto adj_v = adj_list_[u];
		while(adj_v)
		{
			int v_edge_end = adj_v->v_end;
			int weight = adj_v->weight;

			if(in_mst[v_edge_end] == false && weight < key[v_edge_end])
			{
				key[v_edge_end] = weight;
				p[v_edge_end] = u;
				pq.push(make_pair(key[v_edge_end], v_edge_end));
			}
			adj_v = adj_v->next;
		}
	}

	int sum_weight = 0;
	std::cout << "Lista krawedzi MST (v1 - v2; weight): " << std::endl;
	for (int i = 1; i < v_; i++)
	{
		std::cout << "(" << std::setw(3) << p[i] << " - " << std::setw(3) << i << "; ";
		std::cout << std::setw(3) << key[i] << ")" << std::endl;
		sum_weight += key[i];
	}
	std::cout << "Waga MST: " << sum_weight << std::endl;

	delete[] key;
	delete[] p;
	delete[] in_mst;

}

void graph_al_indir::mst_kruskal()
{
	std::vector<edge> edge_list;
	for(int i=0; i<v_; i++)
	{
		auto adj_v = adj_list_[i];
		while (adj_v)
		{
			edge_list.push_back(edge{ i, adj_v->v_end, adj_v->weight });
			adj_v = adj_v->next;
		}
	}

	std::sort(edge_list.begin(), edge_list.end(), [](const edge& a, const edge& b)
	{
		return a.w < b.w;
	});

	auto subsets = new subset[v_];
	for(int i=0; i<v_; i++)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	auto result = new edge[v_];
	int e = 0;
	int i = 0;

	while(e < v_-1 && i < 2*e_)
	{
		edge next_edge = edge_list[i];
		i++;

		int x = find_subset(subsets, next_edge.v1);
		int y = find_subset(subsets, next_edge.v2);

		if (x != y)
		{
			result[e] = next_edge;
			e++;
			union_subsets(subsets, x, y);
		}
	}

	int sum_weight = 0;
	for (int i = 0; i < e; i++)
	{
		std::cout << "(" << std::setw(3) << result[i].v1 << " - " << std::setw(3) << result[i].v2 << "; ";
		std::cout << std::setw(3) << result[i].w << ")" << std::endl;
		sum_weight += result[i].w;
	}
	std::cout << "Waga MST: " << sum_weight << std::endl;

	delete[] subsets;
	delete[] result;
}
