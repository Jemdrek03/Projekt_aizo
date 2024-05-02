#ifndef GENEROWANIEI_H
#define GENEROWANIEI_H
#include "OdczytI.h"
#include <iostream>
#include <random>

// Funkcja generuj¹ca losowe liczby typu int i zapisuj¹ca je do tablicy
DaneInt generujInt()
{
	int rozmiar; //Inicjalizacja zmiennej
	std::cout << "Podaj rozmiar tablicy do wygenerowania: "; //Komunikat
	std::cin >> rozmiar; //Pobranie rozmiaru od uzytkownika
	int* tablica = new int[rozmiar]; //Alokacja pamieci na tablice typu float

	//Te linie kodu konfiguruj¹ system generowania liczb losowych w okreœlonym zakresie.
	//Najpierw tworzony jest losowy generator urz¹dzenia rd, który dostarcza ziarno dla generatora liczb losowych. 
	//Nastêpnie inicjowany jest generator liczb pseudolosowych Mersenne Twister gen za pomoc¹ ziarna z urz¹dzenia rd.
	//Na koniec definiowany jest rozk³ad jednostajny distr, który bêdzie generowaæ losowe liczby rzeczywiste 
	//równomiernie roz³o¿one w zakresie od -100000 do 100000, korzystaj¹c z generatora gen.
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(-100000, 100000); 
	for(int i = 0; i < rozmiar; i++)
	{
		tablica[i] = distr(gen); //Generowanie i przypisanie do tablicy losowej liczby typu int
	}
	DaneInt wynik; //Struktura przechowujaca wynik generatora liczb
	wynik.liczby = tablica; //Przypisanie wskaznika na tablice liczb
	wynik.iloscElementow = rozmiar; //Przypisanie rozmiaru
	return wynik; //Zwrocenie struktury wynikowej
}

// Funkcja generuj¹ca podana liczbe losowych liczb typu float i zapisuj¹ca je do tablicy
DaneInt generujInt(int rozmiar)
{
	int* tablica = new int[rozmiar]; //Alokacja pamieci na tablice typu int 

	//Te linie kodu konfiguruj¹ system generowania liczb losowych w okreœlonym zakresie.
	//Najpierw tworzony jest losowy generator urz¹dzenia rd, który dostarcza ziarno dla generatora liczb losowych. 
	//Nastêpnie inicjowany jest generator liczb pseudolosowych Mersenne Twister gen za pomoc¹ ziarna z urz¹dzenia rd.
	//Na koniec definiowany jest rozk³ad jednostajny distr, który bêdzie generowaæ losowe liczby rzeczywiste 
	//równomiernie roz³o¿one w zakresie od -100000 do 100000, korzystaj¹c z generatora gen.
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distr(-100000, 100000); 
	for (int i = 0; i < rozmiar; i++)
	{
		tablica[i] = distr(gen); //Generowanie i przypisanie do tablicy losowej liczby typu float
	}
	DaneInt wynik; //Struktura przechowujaca wynik generatora liczb
	wynik.liczby = tablica; //Przypisanie wskaznika na tablice liczb
	wynik.iloscElementow = rozmiar; //Przypisanie rozmiaru
	return wynik; //Zwrocenie struktury wynikowej
}

#endif