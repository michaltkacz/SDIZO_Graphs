#pragma once
#include "a_graph_al.h"
#include "i_graph_dir.h"

class graph_al_dir : public a_graph_al, public i_graph_dir
{
public:
	graph_al_dir(int v, int e);

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool is_connected() override;
	void print_graph() override;

	void spf_dijksra(int v_start, int v_end, bool test_performance) override;
	void spf_ford_bellman(int v_start, int v_end, bool test_performance) override;
};
