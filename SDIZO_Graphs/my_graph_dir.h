#pragma once
#include "graph_im_dir.h"
#include "graph_al_dir.h"
#include "my_graph.h"

class my_graph_dir : public my_graph
{
public:
	my_graph_dir();
	~my_graph_dir();

	void init(int v, int e) override;

	void remove() override;

	void random() override;
	void random(int v_number, int density) override;

	void print_graph() override;
	void print_parameters() override;

	bool exists() override;
	bool is_connected() override;

	void spf_dijkstra_al(int v_start, int v_end, bool test_performance = false);
	void spf_dijkstra_im(int v_start, int v_end, bool test_performance = false);
	
	void spf_ford_bellman_al(int v_start, int v_end, bool test_performance = false);
	void spf_ford_bellman_im(int v_start, int v_end, bool test_performance = false);


protected:
	void add_edge(int v_start, int v_end, int e_weight) override;

private:
	graph_im_dir* g_im_dir_;
	graph_al_dir* g_al_dir_;
};
