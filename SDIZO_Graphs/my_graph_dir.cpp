#include "my_graph_dir.h"
#include "my_rand.h"
#include "graph_exception.h"
#include <iostream>
#include <iomanip>

my_graph_dir::my_graph_dir()
{
	g_im_dir_ = nullptr;
	g_al_dir_ = nullptr;
}

my_graph_dir::~my_graph_dir()
{
	my_graph_dir::remove();
}

void my_graph_dir::init(int v, int e)
{
	if(exists())
	{
		remove();
	}

	g_im_dir_ = new graph_im_dir(v, e);
	g_al_dir_ = new graph_al_dir(v, e);
}

void my_graph_dir::remove()
{
	delete g_im_dir_;
	g_im_dir_ = nullptr;

	delete g_al_dir_;
	g_al_dir_ = nullptr;
}

void my_graph_dir::random()
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

		while (g_im_dir_->has_edge(v_start, v_end) || v_start == v_end)
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


	//double density = 0;
	//int v_number = 0;
	//int e_number = 0;
	//do
	//{
	//	density = my_rand::random_percent(min_dens, max_dens);
	//	v_number = my_rand::random_int(min_vert, max_vert);
	//	e_number = a_graph::calculate_edges(v_number, density);
	//	
	//} while (v_number > e_number); //potrzeba min


	//init(v_number, e_number);
	//for (int i = 0; i < e_number; i++)
	//{
	//	int v_start = my_rand::random_int(0, v_number);
	//	int v_end = my_rand::random_int(0, v_number);
	//	int e_weight = my_rand::random_int(min_weight, max_weight);

	//	while (g_im_dir_->has_edge(v_start, v_end) || v_start == v_end)
	//	{
	//		v_start = my_rand::random_int(0, v_number);
	//		v_end = my_rand::random_int(0, v_number);
	//		e_weight = my_rand::random_int(min_weight, max_weight);
	//	}

	//	try
	//	{
	//		add_edge(v_start, v_end, e_weight);
	//	}
	//	catch (graph_exception& e)
	//	{
	//		throw e;
	//	}
	//}

}

void my_graph_dir::print_graph()
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje");
	}

	g_im_dir_->print_graph();
	g_al_dir_->print_graph();
}

void my_graph_dir::print_parameters()
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje");
	}

	std::cout << "Parametry grafu: dens: ";
	std::cout << std::setprecision(2) << g_im_dir_->get_density() << ", v: ";
	std::cout << g_im_dir_->get_v() << ", e: ";
	std::cout << g_im_dir_->get_e() << "." << std::endl;
}

bool my_graph_dir::exists()
{
	return (g_im_dir_ != nullptr && g_al_dir_ != nullptr);
}

bool my_graph_dir::is_connected()
{
	if (!exists())
	{
		return false;
	}

	std::cout << "G_al_dir: " << g_al_dir_->is_connected() << std::endl;
	std::cout << "G_im_dir: " << g_im_dir_->is_connected() << std::endl;

	return g_im_dir_->is_connected();
}

void my_graph_dir::add_edge(int v_start, int v_end, int e_weight)
{
	if (!exists())
	{
		throw graph_exception("Graf nie istnieje!");
	}

	try
	{
		g_im_dir_->add_edge(v_start, v_end, e_weight);
		g_al_dir_->add_edge(v_start, v_end, e_weight);
	}
	catch (graph_exception& e)
	{
		throw e;
	}
}
