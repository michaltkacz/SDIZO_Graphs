#pragma once

class a_graph
{
public:
	a_graph(int v, int e);
	virtual ~a_graph() = default;

	virtual void add_edge(int v_start, int v_end, int e_weight);
	virtual bool find_edge(int v_start, int v_end, int e_weight);
	virtual bool has_edge(int v_start, int v_end);
	virtual bool is_connected() = 0;
	virtual void print_graph() = 0;

	int get_v();
	int get_e();
	double get_density();

	static double calculate_density(int v, int e);
	static int calculate_edges(int v, double d);
	static int calculate_vertices(int e, double d);

protected:
	int e_ = 0;
	int v_ = 0;
	double density_ = 0;
	int curr_edges_ = 0;

	bool check_vertex_good(int v) const;
	bool check_num_edges_good() const;
	bool check_weight_good(int w) const;
};
