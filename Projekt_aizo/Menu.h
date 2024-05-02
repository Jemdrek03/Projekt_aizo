#ifndef MENU_H
#define MENU_H
#include <string>
#include "OdczytI.h";
#include "OdczytF.h";
#include "GenerowanieF.h";
#include "GenerowanieI.h";
#include <chrono>
#include "Przypadki.h"
#include <fstream>

class Menu
{
public:
	static void show_menu()
	{
		int rodzajDanych = -1;
		int* rozmiary = new int[7] {10000, 20000, 30000, 50000, 70000, 90000, 120000};
		std::string nazwaPliku;
		std::ofstream plikWyjsciowy("wynikitest2.txt");
		while (rodzajDanych != 3)
		{
			//Mozliwosc wyboru typu danych
			int zrodloDanych = -1;
			std::cout << "1. Integer" << std::endl;
			std::cout << "2. Float" << std::endl;
			std::cout << "3. Zakoncz program" << std::endl;
			std::cout << "Wybierz rodzaj danych: ";
			//Obsluga blednego wyboru typu danych
			while (!(std::cin >> rodzajDanych) || rodzajDanych < 1 || rodzajDanych > 3) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Wprowadz ponownie: ";
			}
			if (rodzajDanych == 3) break;
			switch (rodzajDanych) {
			case 1:
				while (zrodloDanych != 4) {
					//Mozliwosc wyboru zrodla danych do posortowania
					std::cout << "1. Plik" << std::endl;
					std::cout << "2. Wygeneruj" << std::endl;
					std::cout << "3. Testowanie" << std::endl;
					std::cout << "4. Powrot do wyboru typu danych" << std::endl;
					std::cout << "Wybierz zrodlo danych: ";
					//Obsluga blednego wyboru zrodla danych
					while (!(std::cin >> zrodloDanych) || zrodloDanych < 1 || zrodloDanych > 4) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Wprowadz ponownie: ";
					}
					if (zrodloDanych == 4) break;
					DaneInt wynik;
					switch (zrodloDanych) {
					//Zrodlo danych to plik - otrzymanie nazwy i odczytanie danych z pliku 
					case 1:
						std::cout << "Podaj nazwe pliku: ";
						std::cin >> nazwaPliku;
						wynik = czytajInt(nazwaPliku);
						break;
					//Generacja nowych danych
					case 2:
						wynik = generujInt();
						break;
					//Testowanie
					case 3:
						for (int i = 0; i < 7; i++) {
							//Inicjalizacja zmiennych potrzebnych do otrzymania ostatecznych wynikow testowych
							int rozmiar = rozmiary[i];
							float sumaw = 0.0;
							float czasw = 0.0;
							float sumawb = 0.0;
							float czaswb = 0.0;
							float sumak = 0.0;
							float czask = 0.0;
							float sumas = 0.0;
							float czass = 0.0;
							plikWyjsciowy << "Sortowanie przez wstawianie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujInt(rozmiar); // Generacja danych 
								wynik.liczby = rosnaco<int>(wynik.liczby, rozmiar); //Ewentualne ustawienie poczatkowego rozkladu elementow
								Sortowanie<int> sortowanie = Sortowanie<int>(wynik.liczby, wynik.iloscElementow); //Utworzenie obiektu dla odpowiedniego typu danych
								sortowanie.deepCopy(); //Kopia tablicy, tak aby mozna bylo ja pozniej uzyc ponownie 
								auto t1 = std::chrono::high_resolution_clock::now(); //Zapis czasu rozpoczecia sortowania
								sortowanie.przezWstawianie(); //Sortowanie odpowiednim algorytmem
								auto t2 = std::chrono::high_resolution_clock::now(); //Zapis czasu zakonczenia sortowania
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1); //Obliczenie czasu sortowania
								czasw = ms_int.count(); //Przypisanie czasu do zmienej 
								sumaw += czasw; //Dodanie czasu jednego sortowania do sumy wszystkich pozostalych sortowan
								delete wynik.liczby; //Zwolnienie pamieci 
								delete sortowanie.getArray(); //Zwolnienie pamieci
							}
							//Otrzymanie sredniego czasu sortowania
							sumaw /= 100.0;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czasw << " ms" << std::endl;
	
							//Powtorzenie dla innych metod sortowania
							plikWyjsciowy << "Sortowanie przez wstawianie binarne:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujInt(rozmiar);
								wynik.liczby = procentowe<int>(wynik.liczby, rozmiar, rozmiar * 0.66);
								Sortowanie<int> sortowanie = Sortowanie<int>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.przezWstawianieBinarne();
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czaswb = ms_int.count();
								sumawb += czaswb;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumawb /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czaswb << " ms" << std::endl;
	
							plikWyjsciowy << "Sortowanie przez kopcowanie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujInt(rozmiar);
								wynik.liczby = rosnaco<int>(wynik.liczby, rozmiar);
								Sortowanie<int> sortowanie = Sortowanie<int>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.przezKopcowanie();
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czask = ms_int.count();
								sumak += czask;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumak /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czask << " ms" << std::endl;

							plikWyjsciowy << "Sortowanie szybkie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujInt(rozmiar);
								wynik.liczby = rosnaco<int>(wynik.liczby, rozmiar);
								Sortowanie<int> sortowanie = Sortowanie<int>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.szybkie(0, rozmiar - 1);
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czass = ms_int.count();
								sumas += czass;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumas /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czass << " ms" << std::endl;
		
	
						}
						plikWyjsciowy.close(); 
						break;
					}
					//Obsluga przypadku gdy plik jest bledny
					if (wynik.iloscElementow == 0)
					{
						std::cout << "Bledny plik" << std::endl;
					}
					//Utworzenie obiektu i przejscie do menu sortowania
					else if(zrodloDanych == 1 || zrodloDanych == 2)
					{
						Sortowanie<int> sortowanie = Sortowanie<int>(wynik.liczby, wynik.iloscElementow);
						sortowanie.showMenu();
					}
					//Zwolnienie pamieci
					if (zrodloDanych == 1 || zrodloDanych == 2)
					{
						delete wynik.liczby;
					}
				}
				break;
			//Analogicznie 
			case 2:
				while (zrodloDanych != 4) {
					std::cout << "1. Plik" << std::endl;
					std::cout << "2. Wygeneruj" << std::endl;
					std::cout << "3. Testowanie" << std::endl;
					std::cout << "4. Powrot do wyboru typu danych" << std::endl;
					std::cout << "Wybierz zrodlo danych: ";
					while (!(std::cin >> zrodloDanych) || zrodloDanych < 1 || zrodloDanych > 4) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "Wprowadz ponownie: ";
					}
					if (zrodloDanych == 4) break;
					DaneFloat wynik;
					switch (zrodloDanych) {
					case 1:
						std::cout << "Podaj nazwe pliku: ";
						std::cin >> nazwaPliku;
						wynik = czytajFloat(nazwaPliku);
						break;
					case 2:
						wynik = generujFloat();
						break;
					case 3:
						for (int i = 0; i < 7; i++) {
							int rozmiar = rozmiary[i];
							float sumaw = 0.0;
							float czasw = 0.0;
							float sumawb = 0.0;
							float czaswb = 0.0;
							float sumak = 0.0;
							float czask = 0.0;
							float sumas = 0.0;
							float czass = 0.0;
		
							plikWyjsciowy << "Sortowanie przez wstawianie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujFloat(rozmiar);
								wynik.liczby = rosnaco<float>(wynik.liczby, rozmiar);
								Sortowanie<float> sortowanie = Sortowanie<float>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.przezWstawianie();
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czasw = ms_int.count();
								sumaw += czasw;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumaw /= 100.0;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czasw << " ms" << std::endl;
		
							plikWyjsciowy << "Sortowanie przez wstawianie binarne:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujFloat(rozmiar);
								wynik.liczby = procentowe<float>(wynik.liczby, rozmiar, rozmiar * 0.66);
								Sortowanie<float> sortowanie = Sortowanie<float>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.przezWstawianieBinarne();
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czaswb = ms_int.count();
								sumawb += czaswb;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumawb /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czaswb << " ms" << std::endl;
		
							plikWyjsciowy << "Sortowanie przez kopcowanie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujFloat(rozmiar);
								wynik.liczby = rosnaco<float>(wynik.liczby, rozmiar);
								Sortowanie<float> sortowanie = Sortowanie<float>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.przezKopcowanie();
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czask = ms_int.count();
								sumak += czask;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumak /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czask << " ms" << std::endl;

							plikWyjsciowy << "Sortowanie szybkie:" << std::endl;
							for (int j = 0; j < 100; j++) {
								wynik = generujFloat(rozmiar);
								wynik.liczby = rosnaco<float>(wynik.liczby, rozmiar);
								Sortowanie<float> sortowanie = Sortowanie<float>(wynik.liczby, wynik.iloscElementow);
								sortowanie.deepCopy();
								auto t1 = std::chrono::high_resolution_clock::now();
								sortowanie.szybkie(0, rozmiar - 1);
								auto t2 = std::chrono::high_resolution_clock::now();
								auto ms_int = std::chrono::duration<float, std::milli>(t2 - t1);
								czass = ms_int.count();
								sumas += czass;
								delete wynik.liczby;
								delete sortowanie.getArray();
							}
							sumas /= 100;
							plikWyjsciowy << "Rozmiar tablicy: " << rozmiar << " -> " << czass << " ms" << std::endl;
		
						}
				
						plikWyjsciowy.close(); 

						break;
					}
					if (wynik.iloscElementow == 0)
					{
						std::cout << "Bledny plik" << std::endl;
					}
					else if (zrodloDanych == 1 || zrodloDanych == 2)
					{
						Sortowanie<float> sortowanie = Sortowanie<float>(wynik.liczby, wynik.iloscElementow);
						sortowanie.showMenu();
					}
					if (zrodloDanych == 1 || zrodloDanych == 2)
					{
						delete wynik.liczby;
					}
				}
				break;
			}
		}
	}
};

#endif