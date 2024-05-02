#ifndef ODCZYTF_H
#define ODCZYTF_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// Struktura przechowuj¹ca dane typu float

struct DaneFloat {
	float* liczby;
	float iloscElementow;
};

// Funkcja odczytuj¹ca dane typu float z pliku o podanej nazwie
DaneFloat czytajFloat(const std::string& nazwaPliku)
{
	std::cout << nazwaPliku << std::endl; //Wyswietlenie nazwy pliku
	std::string* linie = nullptr; //Inicjalizacja wskaznika na linie w pliku
	float iloscElementow = 0; //Inicjalizacja zmiennej przechowujacej liczbe elementow 
	DaneFloat wynik; //Inicjalizacja struktury wynikowej
	wynik.liczby = nullptr; //Inicjalizacja wskaznika na tablice liczb typu float 
	wynik.iloscElementow = 0; //Inicjalizacja liczby elementow w tablicy
	std::ifstream plik(nazwaPliku); //Otwarcie pliku o podanej nazwie 
	if (plik.good()) { //Sprawdzenie czy plik zostal poprawnie otworzony 
		std::string linia; //String przechowujacy aktualna linie 
		std::getline(plik, linia); //Odczytanie pierwszej liniii 
		std::istringstream(linia) >> iloscElementow; // Konwersja string na float, otrzymanie ilosci elementow
		if (iloscElementow > 0) { //Sprawdzenie czy znajduja sie jakiekolwiek dane
			linie = new std::string[iloscElementow]; //Alokacja pamieci na tablice typu string
			for (int i = 0; i < iloscElementow; i++) { //Petla odczytujaca kolejne linie 
				if (std::getline(plik, linia)) { //Sprawdzenie poprawnosci odczytania linii z pliku 
					linie[i] = linia; //Przypisanie odczytanej zmiennej 
				}
			}
		}

		float* liczby = new float[iloscElementow]; //Alokacja pamieci na tablice typu float 
		for (int i = 0; i < iloscElementow; i++) {
			std::istringstream(linie[i]) >> liczby[i]; //Petla konwertujaca wszystkie stringi z tablicy na floaty do nowej tablicy 
		}
		delete[] linie; //Zwolnienie pamieci 
		wynik.liczby = liczby;
		wynik.iloscElementow = iloscElementow;
	}
	plik.close();
	return wynik; //Zwrocenie struktury
}

#endif
