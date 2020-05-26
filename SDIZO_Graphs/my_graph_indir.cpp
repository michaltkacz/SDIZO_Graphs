#include "my_graph_indir.h"
#include "graph_exception.h"
#include "my_rand.h"
#include <iostream>
#include <iomanip>

my_graph_indir::my_graph_indir()
{
	g_im_indir_ = nullptr;
	g_al_indir_ = nullptr;
}

my_graph_indir::~my_graph_indir()
{
	my_graph_indir::remove();
}

void my_graph_indir::init(int v, int e)
{
	if (exists())
	{
		remove();
	}

	g_im_indir_ = new graph_im_indir(v, e);
	g_al_indir_ = new graph_al_indir(v, e);
}

void my_graph_indir::remove()
{
	delete g_im_indir_;
	g_im_indir_ = nullptr;

	delete g_al_indir_;
	g_al_indir_ = nullptr;
}

void my_graph_indir::random()
{
	const double density = my_rand::random_percent(min_dens, max_dens);
	const int v_number = my_rand::random_int(min_vert, max_vert);
	const int e_number = a_graph::calculate_edges(v_number, density);

	init(v_number, e_number);
	for (int i = 0; i < e_number; i++)
	{
		int v_start = my_rand::random_int(0, v_number);
		int v_end = my_rand::random_int(0, v_number);
		int e_weight = my_rand::random_int(min_weight, max_weight);

		while (g_im_indir_->has_edge(v_start, v_end) || v_start == v_end)
		{
			v_start = my_rand::random_int(0, v_number);
			v_end = my_rand::random_int(0, v_number);
			e_weight = my_rand::random_int(min_weight, max_weight);
		}

		try
		{
			add_edge(v_start, v_end, e_weight);
		}
		catch (graph_exception& e)
		{
			throw e;
		}
	}
}

void my_graph_indir::print_graph()
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje");
	}

	g_im_indir_->print_graph();
	g_al_indir_->print_graph();
}

void my_graph_indir::print_parameters()
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje");
	}

	std::cout << "Parametry grafu: dens: ";
	std::cout << std::setprecision(2) << g_im_indir_->get_density() << ", v: ";
	std::cout << g_im_indir_->get_v() << ", e: ";
	std::cout << g_im_indir_->get_e() << "." << std::endl;
}

bool my_graph_indir::exists()
{
	return (g_im_indir_ != nullptr && g_al_indir_ != nullptr);
}

bool my_graph_indir::is_connected()
{
	if(!exists())
	{
		return false;
	}

	std::cout << "G_al_indir: " << g_al_indir_->is_connected() << std::endl;
	std::cout << "G_im_indir: " << g_im_indir_->is_connected() << std::endl;

	return g_al_indir_->is_connected();
}

void my_graph_indir::add_edge(int v_start, int v_end, int e_weight)
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje!");
	}

	try
	{
		g_im_indir_->add_edge(v_start, v_end, e_weight);
		g_al_indir_->add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}
}
