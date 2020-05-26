#pragma once
#include <string>


class my_graph
{
public:
	virtual ~my_graph() = default;

	virtual void init(int v, int e) = 0;

	virtual void remove() = 0;
	
	virtual void random() = 0;
	virtual void load_from_file(const std::string& file_name);

	virtual void print_graph() = 0;
	virtual void print_parameters() = 0;

	virtual bool exists() = 0;
	virtual bool is_connected() = 0;

protected:
	virtual void add_edge(int v_start, int v_end, int e_weight) = 0;

	const int min_dens = 10;
	const int max_dens = 100;

	const int min_vert = 5;
	const int max_vert = 31;

	const int min_weight = 0;
	const int max_weight = 100;
};
