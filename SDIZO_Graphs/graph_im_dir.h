#pragma once
#include "a_graph_im.h"
#include "i_graph_dir.h"

class graph_im_dir : public a_graph_im, public i_graph_dir
{
public:
	graph_im_dir(int v, int e);

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool find_edge(int v_start, int v_end, int e_weight) override;
	bool has_edge(int v_start, int v_end) override;
	void print_graph() override;

	void spf_dijksra(int v_start, int v_end) override;
	void spf_ford_bellman(int v_start, int v_end) override;
};
