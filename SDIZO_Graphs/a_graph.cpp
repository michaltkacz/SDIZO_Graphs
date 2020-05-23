#include "a_graph.h"
#include "graph_exception.h"

a_graph::a_graph(int v, int e)
{
	v_ = v;
	e_ = e;
	if(density_ == 0)
	{
		density_ = calculate_density(v_, e_);
	}
}

int a_graph::get_v()
{
	return v_;
}

int a_graph::get_e()
{
	return e_;
}

double a_graph::get_density()
{
	return density_;
}

void a_graph::add_edge(int v_start, int v_end, int e_weight)
{
	if (!check_edge_good())
	{
		throw graph_exception("Zbyt duzo krawedzi");
	}

	if (!check_weight_good(e_weight))
	{
		throw graph_exception("Ujemna waga krawedzi");
	}

	if (!check_vertex_good(v_start))
	{
		throw graph_exception("Poczatkowy wierzcholek nie istnieje");
	}

	if (!check_vertex_good(v_end))
	{
		throw graph_exception("Koncowy wierzcholek nie istnieje");
	}

	if(v_start == v_end)
	{
		throw graph_exception("Poczatkowy i koncowy wierzcholek takie same");
	}

}

bool a_graph::find_edge(int v_start, int v_end, int e_weight)
{
	if (!check_weight_good(e_weight))
	{
		return false;
	}

	if (!check_vertex_good(v_start))
	{
		return false;
	}

	if (!check_vertex_good(v_end))
	{
		return false;
	}

	if (v_start == v_end)
	{
		return false;
	}

	return true;
}



bool a_graph::check_vertex_good(int v) const
{
	return (v >= 0 && v < v_);
}

bool a_graph::check_edge_good() const
{
	return (curr_edges_ >= 0 && curr_edges_ < e_);
}

bool a_graph::check_weight_good(int w) const
{
	return (w >= 0);
}


double a_graph::calculate_density(int v, int e)
{
	return double(2.0 * e ) / double(v*(v - 1.0));
}

int a_graph::calculate_edges(int v, double d)
{
	return int(double(d * v * (v - 1.0)) / 2.0);
}

int a_graph::calculate_vertices(int e, double d)
{
	return int((sqrt(8 * e / d + 1.0) + 1.0) / 2.0);
}


