#pragma once
#include "a_graph.h"

class graph_im : public a_graph
{
public:
	graph_im(int v, int e);
	~graph_im();

	void add_edge(int v_start, int v_end, int e_weight) override;
	bool find_edge(int v_start, int v_end, int e_weight) override;
	void print_graph() override;

private:
	enum edge_dir
	{
		START,
		END
	};

	struct matrix_cell_
	{
		int weight;
		edge_dir dir;
	};
	matrix_cell_*** inc_matrix_; // 2D array of pointers
};
