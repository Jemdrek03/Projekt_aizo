#ifndef GENEROWANIEI_H
#define GENEROWANIEI_H
#include "OdczytI.h"
#include <iostream>
#include <random>

// Funkcja generuj�ca losowe liczby typu int i zapisuj�ca je do tablicy
DaneInt generujInt()
{
	int rozmiar; //Inicjalizacja zmiennej
	std::cout << "Podaj rozmiar tablicy do wygenerowania: "; //Komunikat
	std::cin >> rozmiar; //Pobranie rozmiaru od uzytkownika
	int* tablica = new int[rozmiar]; //Alokacja pamieci na tablice typu float

	//Te linie kodu konfiguruj� system generowania liczb losowych w okre�lonym zakresie.
	//Najpierw tworzony jest losowy generator urz�dzenia rd, kt�ry dostarcza ziarno dla generatora liczb losowych. 
	//Nast�pnie inicjowany jest generator liczb pseudolosowych Mersenne Twister gen za pomoc� ziarna z urz�dzenia rd.
	//Na koniec definiowany jest rozk�ad jednostajny distr, kt�ry b�dzie generowa� losowe liczby rzeczywiste 
	//r�wnomiernie roz�o�one w zakresie od -100000 do 100000, korzystaj�c z generatora gen.
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

// Funkcja generuj�ca podana liczbe losowych liczb typu float i zapisuj�ca je do tablicy
DaneInt generujInt(int rozmiar)
{
	int* tablica = new int[rozmiar]; //Alokacja pamieci na tablice typu int 

	//Te linie kodu konfiguruj� system generowania liczb losowych w okre�lonym zakresie.
	//Najpierw tworzony jest losowy generator urz�dzenia rd, kt�ry dostarcza ziarno dla generatora liczb losowych. 
	//Nast�pnie inicjowany jest generator liczb pseudolosowych Mersenne Twister gen za pomoc� ziarna z urz�dzenia rd.
	//Na koniec definiowany jest rozk�ad jednostajny distr, kt�ry b�dzie generowa� losowe liczby rzeczywiste 
	//r�wnomiernie roz�o�one w zakresie od -100000 do 100000, korzystaj�c z generatora gen.
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