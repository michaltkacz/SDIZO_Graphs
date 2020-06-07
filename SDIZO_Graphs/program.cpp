#include "program.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include "graph_exception.h"
#include <iomanip>
#include "time_logger.h"
#include <fstream>

program::program()
{
	g_dir_ = new my_graph_dir();
	g_indir_ = new my_graph_indir();
}

program::~program()
{
	delete g_dir_;
	g_dir_ = nullptr;
	
	delete g_indir_;
	g_dir_ = nullptr;
}

void program::run()
{
	std::cout << "======================= UWAGA WSTEPNA ======================" << std::endl;
	std::cout << "Opis dzialania poszczegolnych opcji oraz wszelkie zalozenia," << std::endl;
	std::cout << "ktore musza spelniac dane zostaly opisane w zalaczonym" << std::endl;
	std::cout << "do projektu sprawozdaniu w rozdziale \"Program\". Przed" << std::endl;
	std::cout << "rozpoczeciem testowania programu prosze o zapoznanie sie" << std::endl;
	std::cout << "z dokumentem." << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	wait_for_key();

	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "====================== MENU GLOWNE =====================" << std::endl;
		std::cout << "0.Wyjscie" << std::endl;
		std::cout << "9.Uruchom testy algorytmow" << std::endl;
		std::cout << "------------------------- DANE -------------------------" << std::endl;
		std::cout << "1.Wczytaj dane z pliku" << std::endl;
		std::cout << "2.Wygeneruj graf losowo" << std::endl;
		std::cout << "3.Wyswietl graf listowo i macierzowo na ekranie" << std::endl;
		std::cout << "----- WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO -----" << std::endl;
		std::cout << "4.Algorytm Prima" << std::endl;
		std::cout << "5.Algorytm Kruskala" << std::endl;
		std::cout << "------------ WYZNACZANIE NAJKROTSZEJ SCIEZKI -----------" << std::endl;
		std::cout << "6.Algorytm Dijkstry" << std::endl;
		std::cout << "7.Algorytm Forda-Bellmana" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			run_graph_load_from_file_menu();
			break;
		case '2':		
			run_graph_generation_menu();
			break;
		case '3':
			run_print_graph_menu();
			break;
		case '4':
			run_prim_menu();
			break;
		case '5':
			run_kruskal_menu();
			break;
		case '6':
			run_dijkstra_menu();
			break;
		case '7':
			run_ford_bellman_menu();
			break;
		case '9':
			run_tests();
			break;
		case '0':
			std::cout << "Koniec." << std::endl;
			break;
		default: 
			break;
		}
		
	} while (option != '0');

}

void program::run_tests()
{
	auto timer1 = new time_logger();
	auto timer2 = new time_logger();
	auto timer3 = new time_logger();
	auto timer4 = new time_logger();
	auto timer5 = new time_logger();
	auto timer6 = new time_logger();
	auto timer7 = new time_logger();
	auto timer8 = new time_logger();

	const int num_of_dens = 4;
	const int densities[] = { 25, 50, 75, 99 };

	const int num_of_verts = 6;
	const int vertices[] = { 25, 50, 75, 100, 125, 150 };
	
	const int num_of_repeats = 25;

	double times_prim_al[num_of_dens][num_of_verts];
	double times_prim_im[num_of_dens][num_of_verts];
	double times_kruskal_al[num_of_dens][num_of_verts];
	double times_kruskal_im[num_of_dens][num_of_verts];
	double times_dijkstra_al[num_of_dens][num_of_verts];
	double times_dijkstra_im[num_of_dens][num_of_verts];
	double times_ford_bellman_al[num_of_dens][num_of_verts];
	double times_ford_bellman_im[num_of_dens][num_of_verts];

	int current_dens = 0;
	int current_verts = 0;

	for(int dens = 0; dens < num_of_dens; dens++)
	{
		current_dens = densities[dens];

		for(int verts=0; verts<num_of_verts; verts++)
		{
			current_verts = vertices[verts];

			for (int repeat = 0; repeat < num_of_repeats; repeat++)
			{
				// mst
				g_indir_->remove();
				g_indir_->random(current_verts, current_dens);

				timer1->start();
				g_indir_->mst_prim_al(true);
				timer1->stop();

				timer2->start();
				g_indir_->mst_prim_im(true);
				timer2->stop();

				timer3->start();
				g_indir_->mst_kruskal_al(true);
				timer3->stop();

				timer4->start();
				g_indir_->mst_kruskal_im(true);
				timer4->stop();

				// spf
				g_dir_->remove();
				g_dir_->random(current_verts, current_dens);
				
				timer5->start();
				g_dir_->spf_dijkstra_al(0, -1, true);
				timer5->stop();

				timer6->start();
				g_dir_->spf_dijkstra_im(0, -1, true);
				timer6->stop();

				timer7->start();
				g_dir_->spf_ford_bellman_al(0, -1, true);
				timer7->stop();

				timer8->start();
				g_dir_->spf_ford_bellman_im(0, -1, true);
				timer8->stop();
			}

			std::cout << std::endl;
			std::cout << "Test - wierzcholki: " << current_verts;
			std::cout << ", gestosc: " << current_dens << std::endl;
			std::cout << std::setw(30) << "Srednia Prim al: " << std::fixed << std::setprecision(9) << timer1->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Prim im: " << std::fixed << std::setprecision(9) << timer2->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Kruskal al: " << std::fixed << std::setprecision(9) << timer3->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Kruskal im: " << std::fixed << std::setprecision(9) << timer4->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Dijkstra al: " << std::fixed << std::setprecision(9) << timer5->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Dijkstra im: " << std::fixed << std::setprecision(9) << timer6->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Ford-bellman al: " << std::fixed << std::setprecision(9) << timer7->mean() << std::endl;
			std::cout << std::setw(30) << "Srednia Ford-bellman im: " << std::fixed << std::setprecision(9) << timer8->mean() << std::endl;

			times_prim_al[dens][verts] = timer1->mean();
			times_prim_im[dens][verts] = timer2->mean();
			times_kruskal_al[dens][verts] = timer3->mean();
			times_kruskal_im[dens][verts] = timer4->mean();
			times_dijkstra_al[dens][verts] = timer5->mean();
			times_dijkstra_im[dens][verts] = timer6->mean();
			times_ford_bellman_al[dens][verts] = timer7->mean();
			times_ford_bellman_im[dens][verts] = timer8->mean();

			timer1->reset();
			timer2->reset();
			timer3->reset();
			timer4->reset();
			timer5->reset();
			timer6->reset();
			timer7->reset();
			timer8->reset();
		}
	}

	std::ofstream fout("test_results/mst/prim_al.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_prim_al[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/mst/prim_im.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_prim_im[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/mst/kruskal_al.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_kruskal_al[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/mst/kruskal_im.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_kruskal_im[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/spf/dijkstra_al.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_dijkstra_al[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/spf/dijkstra_im.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_dijkstra_im[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/spf/ford_bellman_al.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_ford_bellman_al[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	fout.open("test_results/spf/ford_bellman_im.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < num_of_dens; i++)
		{
			for (int j = 0; j < num_of_verts; j++)
			{
				fout << std::fixed << std::setprecision(9) << times_ford_bellman_im[i][j] << " ";
			}
			fout << std::endl;
		}
	}
	fout.close();

	delete timer1;
	delete timer2;
	delete timer3;
	delete timer4;
	delete timer5;
	delete timer6;
	delete timer7;
	delete timer8;

	std::cout << "Koniec testow. Wyniki zostaly zapisane." << std::endl;
	wait_for_key();
}

void program::run_graph_load_from_file_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "====================== MENU PLIKU ======================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wczytaj dane do grafu skierowanego" << std::endl;
		std::cout << "2.Wczytaj dane do grafu nieskierowanego" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			try
			{
				g_dir_->remove();
				g_dir_->load_from_file(file_name);
				std::cout << "Dane zostaly wczytane." << std::endl;
				if(!g_dir_->is_connected())
				{
					std::cout << "Uwaga: wczytany graf nie jest spojny!" << std::endl;
				}
				else
				{
					std::cout << "Graf jest spojny." << std::endl;
				}
				
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wczytywanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		}
		case '2':
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			try
			{
				g_indir_->remove();
				g_indir_->load_from_file(file_name);
				std::cout << "Dane zostaly wczytane." << std::endl;
				if (!g_indir_->is_connected())
				{
					std::cout << "Uwaga: wczytany graf nie jest spojny!" << std::endl;
				}
				else
				{
					std::cout << "Graf jest spojny." << std::endl;
				}
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wczytywanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		}
		default:
			break;
		}

	} while (option != '0');
}

void program::run_graph_generation_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "==================== MENU GENEROWANIA ==================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wygeneruj graf skierowany (parametry uzytkownika)" << std::endl;
		std::cout << "2.Wygeneruj graf nieskierowany (parametry uzytkownika)" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "3.Wygeneruj graf skierowany (parametry losowe)" << std::endl;
		std::cout << "4.Wygeneruj graf nieskierowany (parametry losowe)" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
		{
			int v = 0;
			int d = 0;
			std::cout << "Podaj liczbe wierzcholkow (5-150)\nv=";
			std::cin >> v;
			std::cout << "Podaj gestosc(1-99)\nd=";
			std::cin >> d;
			try
			{
				g_dir_->remove();
				g_dir_->random(v, d);
				g_dir_->print_parameters();
				std::cout << "Graf zostal wygenerowany." << std::endl;
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Tworzenie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		}
		case '2':
		{
			int v = 0;
			int d = 0;
			std::cout << "Podaj liczbe wierzcholkow (5-150)\nv=";
			std::cin >> v;
			std::cout << "Podaj gestosc(1-99)\nd=";
			std::cin >> d;
			try
			{
				g_indir_->remove();
				g_indir_->random(v, d);
				g_indir_->print_parameters();
				std::cout << "Graf zostal wygenerowany." << std::endl;
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Tworzenie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		}
		case '3':
			try
			{
				g_dir_->remove();
				g_dir_->random();
				g_dir_->print_parameters();
				std::cout << "Graf zostal wygenerowany." << std::endl;
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Tworzenie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		case '4':
			try
			{
				g_indir_->remove();
				g_indir_->random();
				g_indir_->print_parameters();
				std::cout << "Graf zostal wygenerowany." << std::endl;
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Tworzenie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_print_graph_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "===================== MENU WYPISANIA ===================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wyswietl graf skierowany" << std::endl;
		std::cout << "2.Wyswietl graf nieskierowany" << std::endl;
		std::cout << "3.Wyswietl oba grafy" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			try
			{
				g_dir_->print_parameters();
				g_dir_->print_graph();
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wypisanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		case '2':
			try
			{
				g_indir_->print_parameters();
				g_indir_->print_graph();
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wypisanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		case '3':
			try
			{
				g_dir_->print_parameters();
				g_dir_->print_graph();
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wypisanie grafu przerwane!" << std::endl;
			}

			try
			{
				g_indir_->print_parameters();
				g_indir_->print_graph();
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wypisanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_prim_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "===================== ALGORYTM PRIMA ===================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wykonaj na reprezentacji listowej" << std::endl;
		std::cout << "2.Wykonaj na reprezentacji macierzowej" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			if(g_indir_->is_connected())
			{
				g_indir_->mst_prim_al();
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Prima przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		case '2':
			if (g_indir_->is_connected())
			{
				g_indir_->mst_prim_im();
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Prima przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_kruskal_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "==================== ALGORYTM KRUSKALA =================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wykonaj na reprezentacji listowej" << std::endl;
		std::cout << "2.Wykonaj na reprezentacji macierzowej" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			if (g_indir_->is_connected())
			{
				g_indir_->mst_kruskal_al();
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Kruskala przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		case '2':
			if (g_indir_->is_connected())
			{
				g_indir_->mst_kruskal_im();
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Kruskala przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_dijkstra_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "==================== ALGORYTM DIJKSTRY =================" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wykonaj na reprezentacji listowej" << std::endl;
		std::cout << "2.Wykonaj na reprezentacji macierzowej" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			if (g_dir_->is_connected())
			{
				int v_start = 0;
				int v_end = 0;
				std::cout << "Podaj wierzcholek poczatkowy: ";
				std::cin >> v_start;
				std::cout << "Podaj wierzcholek koncowy (-1 wyswietlenie drog do wszystkich wierzcholkow): ";
				std::cin >> v_end;

				try
				{
					g_dir_->spf_dijkstra_al(v_start, v_end);
				}catch(graph_exception& e)
				{
					std::cout << "Blad: ";
					std::cout << e.what() << std::endl;
					std::cout << "Algorytm Dijkstry przerwany!" << std::endl;
				}	
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Dijkstry przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		case '2':
			if (g_dir_->is_connected())
			{
				int v_start = 0;
				int v_end = 0;
				std::cout << "Podaj wierzcholek poczatkowy: ";
				std::cin >> v_start;
				std::cout << "Podaj wierzcholek koncowy (-1 wyswietlenie drog do wszystkich wierzcholkow): ";
				std::cin >> v_end;

				try
				{
					g_dir_->spf_dijkstra_im(v_start, v_end);
				}
				catch (graph_exception& e)
				{
					std::cout << "Blad: ";
					std::cout << e.what() << std::endl;
					std::cout << "Algorytm Dijkstry przerwany!" << std::endl;
				}
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Dijkstry przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_ford_bellman_menu()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "================= ALGORYTM FORDA-BELLMANA ==============" << std::endl;
		std::cout << "0.Powrot" << std::endl;
		std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << "1.Wykonaj na reprezentacji listowej" << std::endl;
		std::cout << "2.Wykonaj na reprezentacji macierzowej" << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			if (g_dir_->is_connected())
			{
				int v_start = 0;
				int v_end = 0;
				std::cout << "Podaj wierzcholek poczatkowy: ";
				std::cin >> v_start;
				std::cout << "Podaj wierzcholek koncowy (-1 wyswietlenie drog do wszystkich wierzcholkow): ";
				std::cin >> v_end;

				try
				{
					g_dir_->spf_ford_bellman_al(v_start, v_end);
				}
				catch (graph_exception& e)
				{
					std::cout << "Blad: ";
					std::cout << e.what() << std::endl;
					std::cout << "Algorytm Forda-Bellmana przerwany!" << std::endl;
				}
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Forda-Bellmana przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		case '2':
			if (g_dir_->is_connected())
			{
				int v_start = 0;
				int v_end = 0;
				std::cout << "Podaj wierzcholek poczatkowy: ";
				std::cin >> v_start;
				std::cout << "Podaj wierzcholek koncowy (-1 wyswietlenie drog do wszystkich wierzcholkow): ";
				std::cin >> v_end;

				try
				{
					g_dir_->spf_ford_bellman_im(v_start, v_end);
				}
				catch (graph_exception& e)
				{
					std::cout << "Blad: ";
					std::cout << e.what() << std::endl;
					std::cout << "Algorytm Forda-Bellmana przerwany!" << std::endl;
				}
			}
			else
			{
				std::cout << "Blad: ";
				std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
				std::cout << "Algorytm Forda-Bellmana przerwany!" << std::endl;
			}
			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::wait_for_key()
{
	std::cout << "Wcisnij [ENTER] aby kontynuowac.\n";
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
