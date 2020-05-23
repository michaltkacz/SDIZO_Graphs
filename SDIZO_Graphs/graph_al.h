#pragma once
#include "a_graph.h"
#include <list>

class graph_al : public a_graph
{
public:
	graph_al(int v, int e);

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool find_edge(int v_start, int v_end, int e_weight) override;
	void print_graph() override;

private:
	std::list<int, int> *v_list_;
};
