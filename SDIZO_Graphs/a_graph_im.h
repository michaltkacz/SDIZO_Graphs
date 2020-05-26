#pragma once
#include "a_graph.h"

class a_graph_im : public a_graph
{
public:
	a_graph_im(int v, int e);
	~a_graph_im();

	bool is_connected() override;
	void print_graph() override;
protected:
	int*** inc_matrix_; // 2D array of pointers to int
};
