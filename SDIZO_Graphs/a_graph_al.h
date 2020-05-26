#pragma once
#include "a_graph.h"

class a_graph_al : public a_graph
{
public:
	a_graph_al(int v, int e);
	~a_graph_al();

	void add_edge(int v_start, int v_end, int e_weight) override;
    bool find_edge(int v_start, int v_end, int e_weight) override;
    bool has_edge(int v_start, int v_end) override;
	void print_graph() override;

protected:
	struct adj_list_el {
		int v_end;
		int weight;
		adj_list_el* next;
	};

	adj_list_el** adj_list_;

};
