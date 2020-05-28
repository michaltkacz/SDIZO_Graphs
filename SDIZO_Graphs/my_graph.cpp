#include "my_graph.h"
#include "graph_exception.h"
#include "my_rand.h"
#include <fstream>
#include <iomanip>


void my_graph::random()
{
	const int v_number = my_rand::random_int(min_vert, max_vert);
	const int density = my_rand::random_int(min_dens, max_dens);
	random(v_number, density);
}

void my_graph::random(int v_number, int density)
{
	if (v_number < min_vert || v_number >= max_vert)
	{
		throw graph_exception("Liczba wierzcholkow poza zakresem! (5-50)");
	}

	if(density < min_dens || density >= max_dens)
	{
		throw graph_exception("Gestosc poza zakresem! (1%-99%)");
	}

}

void my_graph::load_from_file(const std::string& file_name)
{
	std::ifstream fin(file_name);
	if (fin.is_open())
	{
		int e = 0;
		int v = 0;
		int v_start = 0;
		int v_end = 0;
		int w = 0;

		fin >> e;
		fin >> v;
		try
		{
			init(v, e);
			while (!fin.eof())
			{
				fin >> v_start;
				fin >> v_end;
				fin >> w;

				add_edge(v_start, v_end, w);
			}
		}
		catch (graph_exception& exc)
		{
			fin.close();
			throw exc;
		}
		fin.close();
	}
	else
	{
		throw graph_exception("Podany plik nie istnieje!");
	}
}
