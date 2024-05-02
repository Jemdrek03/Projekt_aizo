// Projekt_aizo.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
#include <iostream>
#include "Sortowanie.h"
#include "OdczytI.h"
#include "OdczytF.h"
#include "GenerowanieI.h"
#include "GenerowanieF.h"
#include "Menu.h"
#include "Przypadki.h"

int main()
{
	Menu::show_menu();
	std::cin.ignore(1);
	std::cin.get();
}

