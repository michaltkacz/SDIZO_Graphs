#pragma once

class i_graph_indir
{
public:
	virtual void mst_prim(int v_start) = 0;
	virtual void mst_kruskal(int v_start) = 0;
};
