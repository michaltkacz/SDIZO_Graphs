#pragma once
#include "graph_im.h"

class program
{
public:
	program();
		~program();

	void run();

private:
	void print_main_menu() const;
	void wait_for_key();

	void delete_current_graph();
	void create_random_graph();
	void load_graph_from_file();

	void print_graph();
	

	graph_im* g_im_;
	graph_im* g_al_;

};
