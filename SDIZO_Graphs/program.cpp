#include "program.h"
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include "graph_im.h"
#include "graph_exception.h"
#include "my_rand.h"


program::program()
{
	g_im_ = nullptr;
	g_al_ = nullptr;
}

program::~program()
{
	delete_current_graph();
}

void program::run()
{
	char option;
	do {
		system("cls");
		print_main_menu();
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':

			break;
		case '2':		
			try
			{
				delete_current_graph();
				create_random_graph();
				std::cout << "Graf zostal wygnerowany" << std::endl;
			}
			catch (graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Tworzenie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		case '3':
			try
			{
				print_graph();
			}
			catch(graph_exception& e)
			{
				std::cout << "Blad: ";
				std::cout << e.what() << std::endl;
				std::cout << "Wypisanie grafu przerwane!" << std::endl;
			}
			wait_for_key();
			break;
		case '4':

			break;
		case '5':

			break;
		case '6':

			break;
		case '7':

			break;
		case '9':

			break;
		}
		
	} while (option != '0');

}

void program::print_main_menu() const
{
	std::cout << std::endl;
	std::cout << "====================== MENU GLOWNE =====================" << std::endl;
	std::cout << "0.Wyjscie" << std::endl;
	std::cout << "0.Uruchom testy algorytmow (wymaga okolo XX minut)" << std::endl;
	std::cout << "------------------------- DANE -------------------------" << std::endl;
	std::cout << "1. Wczytaj dane z pliku" << std::endl;
	std::cout << "2. Wygeneruj graf losowo" << std::endl;
	std::cout << "3. Wyswietl graf listowo i macierzowo na ekranie" << std::endl;
	std::cout << "----- WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO -----" << std::endl;
	std::cout << "4. Algorytm Prima" << std::endl;
	std::cout << "5. Algorytm Kruskala" << std::endl;
	std::cout << "------------ WYZNACZANIE NAJKROTSZEJ SCIEZKI -----------" << std::endl;
	std::cout << "6. Algorytm Dijkstry" << std::endl;
	std::cout << "7. Algorytm Forda-Bellmana" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "Podaj opcje:";
}

void program::delete_current_graph()
{
	delete g_im_;
	g_im_ = nullptr;

	delete g_al_;
	g_im_ = nullptr;
}

void program::create_random_graph()
{
	const int min_dens = 1;
	const int max_dens = 100;

	const int min_vert = 5;
	const int max_vert = 21;

	const int min_weight = 0;
	const int max_weight = 100;

	const double density = my_rand::random_percent(min_dens, max_dens);
	const int v_number = my_rand::random_int(min_vert, max_vert);
	const int e_number = a_graph::calculate_edges(v_number, density);

	std::cout << density << ", ";
	std::cout << v_number << ", ";
	std::cout << e_number << std::endl;

	g_im_ = new graph_im(v_number, e_number);
	//g_al_ = new graph_im(v_number, e_number);
	for (int i = 0; i < e_number; i++)
	{
		int v_start = my_rand::random_int(0, v_number);
		int v_end = my_rand::random_int(0, v_number);
		int e_weight = my_rand::random_int(min_weight, max_weight);

		while (g_im_->find_edge(v_start, v_end, e_weight) || v_start == v_end)
		{
			v_start = my_rand::random_int(0, v_number);
			v_end = my_rand::random_int(0, v_number);
			e_weight = my_rand::random_int(min_weight, max_weight);
		}

		try
		{
			g_im_->add_edge(v_start, v_end, e_weight);
			//g_al_->add_edge(v_start, v_end, e_weight);
		}
		catch (graph_exception& e)
		{
			throw e;
		}
	}
}

void program::load_graph_from_file()
{
}

void program::print_graph()
{
	//if(g_im_ == nullptr || g_al_ == nullptr)
	if(g_im_ == nullptr)
	{
		throw graph_exception("Graf nie istnieje");
	}

	g_im_->print_graph();
	//g_al_->print_graph();
}

void program::wait_for_key()
{
	std::cout << "Wcisnij [ENTER] aby kontynuowac.\n";
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


