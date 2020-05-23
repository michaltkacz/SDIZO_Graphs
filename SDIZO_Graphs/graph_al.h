#pragma once
#include "a_graph.h"
#include <list>

class graph_al : public a_graph
{
public:
	graph_al(int v, int e);
	~graph_al();

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool find_edge(int v_start, int v_end, int e_weight) override;
	void print_graph() override;

private:
	struct adj_list_el {
		int v_end;
		int weight;
		adj_list_el* next;
	};

	adj_list_el** adj_list_;

};
