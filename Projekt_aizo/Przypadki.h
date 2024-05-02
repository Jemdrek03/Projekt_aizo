#ifndef PRZYPADKI_H
#define PRZYPADKI_H
#include "Sortowanie.h"
#include <algorithm>

template <typename T>
T* rosnaco(T* data, int size)
{
	Sortowanie<T> sortowanie = Sortowanie<T>(data, size); //Utworzenie obiektu sortowanie 
	sortowanie.deepCopy(); //Kopia danych, aby mozna bylo prowadzic dalsze operacje na tych samych danych
	sortowanie.szybkie(0, size-1); //Posortowanie tablicy rosnaco
	data = sortowanie.getArray(); //Przypisanie nowych danych 
	return data; //Zwrocenie posortowanych rosnaco danych 
}

template <typename T>
T* malejaco(T* data, int size)
{
	Sortowanie<T> sortowanie = Sortowanie<T>(data, size); //Utworzenie obiektu sortowanie
	sortowanie.deepCopy(); //Kopia danych, aby mozna bylo prowadzic dalsze operacje na tych samych danych
	sortowanie.szybkie(0, size - 1); //Posortowanie tablicy rosnaco
	data = sortowanie.getArray(); //Przypisanie nowych danych
	for(int i = 0; i < size/2; i++){
		sortowanie.swap(data, i, size - 1 - i); //Swap elementow, tak aby tablica byla posortowana malejaco
	}
	return data; //Zwrocenie posortowanych malejaco danych
}

template <typename T>
T* procentowe(T* data, int size, int n)
{
	Sortowanie<T> sortowanie = Sortowanie<T>(data, size); //Utworzenie obiektu sortowanie
	sortowanie.deepCopy(); //Kopia danych, aby mozna bylo prowadzic dalsze operacje na tych samych danych
	sortowanie.szybkie(0, size - 1); //Posortowanie tablicy rosnaco
	data = sortowanie.getArray(); //Przypisanie nowych danych
	std::random_shuffle(&data[n+1], &data[size - 1]); //Wymieszanie czesci elementow
	return data; //Zwrocenie danych, gdzie pewna czesc z nich jest posortowana, a reszta jest losowa  
}

#endif
