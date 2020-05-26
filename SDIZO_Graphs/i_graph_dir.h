#pragma once

class i_graph_dir
{
public:
	virtual void spf_dijksra(int v_start, int v_end) = 0;
	virtual void spf_ford_bellman(int v_start, int v_end) = 0;
};
