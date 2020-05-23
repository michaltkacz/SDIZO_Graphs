#pragma once
#include "graph_im.h"
#include <string>
#include "graph_al.h"

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
	void load_graph_from_file(std::string file_name);

	void print_graph();
	void print_graph_parameters();

	bool graph_exists();

	graph_im* g_im_;
	graph_al* g_al_;

};
