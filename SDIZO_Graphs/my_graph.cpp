#include "my_graph.h"
#include "graph_exception.h"
#include "my_rand.h"
#include <fstream>
#include <iomanip>


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
