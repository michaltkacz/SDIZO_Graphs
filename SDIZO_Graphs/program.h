#pragma once
#include "my_graph.h"
#include "my_graph_indir.h"
#include "my_graph_dir.h"

class program
{
public:
	program();
	~program();

	void run();

private:
	my_graph_dir* g_dir_;
	my_graph_indir* g_indir_;


	void run_tests();

	void run_graph_load_from_file_menu();
	void run_graph_generation_menu();
	void run_print_graph_menu();
	
	void run_prim_menu();
	void run_kruskal_menu();
	
	void run_dijkstra_menu();
	void run_ford_bellman_menu();
	

	void wait_for_key();

};
