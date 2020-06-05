#pragma once
#include "i_graph_indir.h"
#include "a_graph_im.h"

class graph_im_indir : public a_graph_im, public i_graph_indir
{
public:
	graph_im_indir(int v, int e);

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool find_edge(int v_start, int v_end, int e_weight) override;
	bool has_edge(int v_start, int v_end) override;
	void print_graph() override;

	void mst_prim(bool test_performance) override;
	void mst_kruskal(bool test_performance) override;

};
