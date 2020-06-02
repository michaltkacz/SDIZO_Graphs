#include "graph_im_indir.h"
#include "graph_exception.h"
#include <ostream>
#include <iostream>
#include <queue>
#include <iomanip>

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

void graph_im_indir::mst_prim()
{
	using namespace std;
	const int NIL = -1;
	int v_start = 0;
	auto key = new int[v_];
	auto p = new int[v_];
	auto in_mst = new bool[v_];
	for (int i = 0; i < v_; i++)
	{
		key[i] = INT_MAX;
		p[i] = NIL;
		in_mst[i] = false;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	key[v_start] = 0;
	pq.push(make_pair(key[v_start], v_start));

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		in_mst[u] = true;

		for(int i=0; i < e_; i++)
		{
			if(inc_matrix_[u][i] != nullptr)
			{
				for(int j=0; j<v_; j++)
				{
					if(j != u && inc_matrix_[j][i] != nullptr)
					{
						if (in_mst[j] == false && *inc_matrix_[j][i] < key[j])
						{
							key[j] = *inc_matrix_[j][i];
							p[j] = u;
							pq.push(make_pair(key[j], j));
						}
					}
				}
			}
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

void graph_im_indir::mst_kruskal()
{
	std::vector<edge> edge_list;
	for (int i = 0; i < e_; i++)
	{
		int j = 0;
		int v1 = 0;
		int v2 = 0;
		int w = 0;
		while(j<v_)
		{
			if (inc_matrix_[j][i] != nullptr)
			{
				v1 = j;
				w = *inc_matrix_[j][i];
				j++;
				break;
			}
			j++;
		}

		while (j < v_)
		{
			if (inc_matrix_[j][i] != nullptr)
			{
				v2 = j;
				break;
			}
			j++;
		}
		edge_list.push_back(edge{ v1, v2, w });
	}


	std::sort(edge_list.begin(), edge_list.end(), [](const edge& a, const edge& b)
	{
		return a.w < b.w;
	});

	auto subsets = new subset[v_];
	for (int i = 0; i < v_; i++)
	{
		subsets[i].parent = i;
		subsets[i].rank = 0;
	}

	auto result = new edge[v_];
	int e = 0;
	int i = 0;

	while (e < v_ - 1 && i < 2 * e_)
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
