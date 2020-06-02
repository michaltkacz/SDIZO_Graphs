#include "program.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include "graph_exception.h"
#include <iomanip>

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
	std::cout << "===================== UWAGA WSTEPNA =====================" << std::endl;
	std::cout << "Opis dzialania poszczegolnych opcji oraz wszelkie" << std::endl;
	std::cout << "zalozenia, ktore musza spelniac grafy zostaly opisane" << std::endl;
	std::cout << "w zalaczonym do projektu sprawozdaniu. Przed rozpoczeciem" << std::endl;
	std::cout << "testowania programu prosze o zapoznanie sie z dokumentem." << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
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
			std::cout << "Podaj liczbe wierzcholkow (5-50)\nv=";
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
			std::cout << "Podaj liczbe wierzcholkow (0-50)\nv=";
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
		std::cout << "2.Wyswietl oba grafy" << std::endl;
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
				g_indir_->mst_prim_al(0);
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
				g_indir_->mst_prim_im(0);
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
			//if (g_dir_->is_connected())
			//{
			//	g_dir_->spf_dijkstra_al(0, 5);
			//}
			//else
			//{
			//	std::cout << "Blad: ";
			//	std::cout << "Graf nie jest spojny lub nie istnieje!" << std::endl;
			//	std::cout << "Algorytm Prima przerwany!" << std::endl;
			//}
			wait_for_key();
			break;
		case '2':

			wait_for_key();
			break;
		default:
			break;
		}

	} while (option != '0');
}

void program::run_ford_bellman_menu()
{
}

void program::wait_for_key()
{
	std::cout << "Wcisnij [ENTER] aby kontynuowac.\n";
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
