#pragma once
#include "i_graph_indir.h"
#include "a_graph_al.h"

class graph_al_indir : public a_graph_al, public i_graph_indir
{
public:
	graph_al_indir(int v, int e);

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool is_connected() override;
	void print_graph() override;

	void mst_prim(int v_start) override;
	void mst_kruskal() override;
};
