#ifndef SORTOWANIE_H
#define SORTOWANIE_H

template <typename T>
class Sortowanie
{
	private:
		T* originalData; //Wskaznik na oryginalne dane 
		T* array; //Wskaznik na tablice danych 
		int size; //Rozmiar tablicy 

	public:
		T* getArray(){
			return array;
		}
		
		Sortowanie(T* data, int size) {
			this->originalData = data; //Przypisanie wskaznika na oryginalne dane 
			this->size = size; //Przypisanie rozmiaru tablicy 
		}

		void wyswietlTablice(T* dane, int size){
			for(int i = 0; i < size; i++){ 
				std::cout << dane[i] << " "; //Wyswietlanie tablicy 
			}
			std::cout << std::endl;
		}

		void showMenu(){
			int algorytm = -1;
			while(algorytm != 5){
				//Mozliwosc wyboru algorytmu sortowania
				std::cout << "1. Przez wstawianie" << std::endl;
				std::cout << "2. Przez wstawianie binarne" << std::endl;
				std::cout << "3. Przez kopcowanie" << std::endl;
				std::cout << "4. Szybkie" << std::endl;
				std::cout << "5. Powrot do menu danych" << std::endl;
				std::cout << "Wybierz algorytm sortowania: ";
				//Obsluga blednego wyboru algorytmu
				while (!(std::cin >> algorytm) || algorytm < 1 || algorytm > 5) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Wprowadz ponownie: ";
				}
				if (algorytm == 5) break;
				//Wyswietlenie tablicy przed sortowaniem 
				std::cout << "Dane przed sortowaniem: ";
				wyswietlTablice(this->originalData, this->size);
				deepCopy(); //Kopia oryginalnych danych, tak aby mozna bylo prowadzic dalsze operacje na tych samych danych 
				//Switch z roznymi sposobami sortowania 
				switch (algorytm) {
				case 1:
					przezWstawianie();
					break;
				case 2:
					przezWstawianieBinarne();
					break;
				case 3:
					przezKopcowanie();
					break;
				case 4:
					szybkie(0, this->size-1);
					break;
				}
				//wyswietlanie tablicy po sortowaniu
				std::cout << "Dane po sortowaniu: ";
				wyswietlTablice(this->array, this->size);
				delete array; //Zwolnienie pamieci 
			}
		}

		void deepCopy(){
			this->array = new T[size]; //Alokacja pamieci dla tablicy 
			std::memcpy(this->array, this->originalData, sizeof(T) * size); //Kopia danych do tablicy 
			this->size = size; //Przypisanie rozmiaru 
		}

		void swap(T* array, int index1, int index2){
			int tmp = array[index1];
			array[index1] = array[index2]; //Zamiana elementow miejscami
			array[index2] = tmp;
			return;
		}

		//Sortowanie przez wstawianie
		//Ustawienie i na 1, poniewaz uznajemy ze pierwszy element jest posortowany
		//Petla po calej tablicy, w momencie gdy poprzedni element jest wiekszy nastepuje zamiana elementow
		//Zamiana trwa do momentu gdy dany element znajduje sie na odpowiednim miejscu 
		void przezWstawianie(){
			int i = 1;
			int j;
			while (i < this->size) {
				j = i;
				while (j > 0 && this->array[j] < this->array[j-1]) {
					swap(this->array, j, j - 1);
					j--;
				}
				i++;
			}
		}

		//Wyszukiwanie binarne
		//Dzielenie tablicy na pol i porownanie elementu szukanego z koncowym
		//W momencie gdy granice przeszukiwania beda takie same to zostaje zwracany indeks
		//gdzie znaleziono element lub indeks kolejnego, wiekszego elementu 
		int wyszukiwanieBinarne(int item,int lewy, int prawy)
		{
			if (prawy <= lewy)
			{
				if (item > this->array[lewy])
				{
					return (lewy + 1);
				}
				else
				{
					return lewy;
				}
			}
			int srodek = (lewy + prawy) / 2;
			if (item == this->array[srodek])
			{
				return (srodek + 1);
			}
			if (item > this->array[srodek])
			{
				return wyszukiwanieBinarne(item, srodek + 1, prawy);
			}
			return wyszukiwanieBinarne(item, lewy, srodek - 1);
		}

		//Wstawianie binarne
		//Dziala analogicznie do zwyklego sortowania przez wstawianie
		//Roznica polega na tym, ze gdy element poprzedni jest wiekszy od aktualnego
		//To zostaje uruchomione wyszukiwanie binarne, ktore znajduje odpowiednie miejsce dla elementu porownywanego
		//Elementy dalsze zostaja przesuniete o jedno miejsce do przodu 
		void przezWstawianieBinarne()
		{
			int i = 1, j, element, miejsce;

			while (i < this->size)
			{
				j = i - 1;
				element = this->array[i];

				miejsce = wyszukiwanieBinarne(element, 0, j);

				while (j >= miejsce)
				{
					this->array[j + 1] = this->array[j];
					j--;
				}
				this->array[j + 1] = element;
				i++;
			}
		}

		void naprawaKopcaWDol(int liczbaElementow, int index)
		{
			int najwiekszy = index; // Inicjalizacja zmiennej najwiêkszy jako indeks wêz³a w kopcu.
			int lewy =  2 * index + 1; // Obliczenie indeksu lewego dziecka w kopcu.
			int prawy = 2 * index + 2; // Obliczenie indeksu prawego dziecka w kopcu.

			// Sprawdzenie czy lewe dziecko istnieje i czy jest wiêksze od rodzica.
			if (lewy < liczbaElementow && this->array[lewy] > this->array[najwiekszy])
				najwiekszy = lewy;

			// Sprawdzenie czy prawe dziecko istnieje i czy jest wiêksze od rodzica lub od lewego dziecka.
			if (prawy < liczbaElementow && this->array[prawy] > this->array[najwiekszy])
				najwiekszy = prawy;

			if (najwiekszy != index) { // Jeœli indeks najwiêkszego elementu nie jest równy indeksowi obecnego wêz³a.
				swap(this->array, index, najwiekszy); // Zamiana miejscami obecnego wêz³a z wêz³em o wiêkszej wartoœci.
				naprawaKopcaWDol(liczbaElementow, najwiekszy); // Rekurencyjne wywo³anie funkcji naprawy kopca w dó³ dla wêz³a o najwiêkszej wartoœci.
			}
		}

		//Tworzenie kopca, zamiana tablicy danych na kopiec
		void stworzKopiec()
		{
			for (int i = (this->size - 2) / 2; i >= 0; --i) {
				naprawaKopcaWDol(this->size, i);
			}
		}

		//Najpierw tworzony jest kopiec, nastepnie korzen i ostatni elemnt zostaja zamienione, przez co otrzymujemy najwiekszy element na odpowiednim miejscu
		//Po ustawieniu elementu najwiekszego na odpowiednim miejscu, kopiec zostaje naprawiony, i posiada o jeden element mniej
		//Operacje te wykonuja sie dla kazdego elementu w kopcu
		void przezKopcowanie()
		{
			stworzKopiec(); // Tworzenie kopca.
			for (int i = this->size - 1;  i > 0; i--) { // Iteracja od ostatniego elementu do drugiego.
				swap(this->array, 0, i); // Zamiana miejscami korzenia kopca (pierwszego elementu) z ostatnim elementem w nieposortowanej czêœci tablicy.
				naprawaKopcaWDol(i, 0); // Naprawa kopca w dó³ dla kopca zredukowanego o jeden element.
			}
		}

		//Wskazniki l i r poruszaja sie zamieniajac elementy tak aby elementy mniejsze byly na lewo od pivota,
		//A elementy wieksze na prawo od piwota
		int partycja(int low, int high)
		{
			//Ustawienie pivota na srodku i przyjecie odpowiednich granic 
			T pivot = this->array[(low + high) / 2];
			int l = low;
			int r = high;


			while (true) {
				//Ustawienie l i r na odpowiednim miejscach
				while (this->array[l] < pivot) ++l;
				while (this->array[r] > pivot) --r;

				// Jeœli wskaŸnik l jest mniejszy od r, zamieñ elementy na pozycjach l i r.
				if (l < r) {
					swap(this->array, l, r);
					++l;
					--r;
				}
				// Jeœli wskaŸnik l jest wiêkszy lub równy r, zakoñcz partycjonowanie.
				else {
					if (r == high) r--; // Jeœli wskaŸnik r wskazuje na ostatni element, przesuñ go w lewo.
					return r; // Zwróæ indeks ostatniego elementu w lewej czêœci tablicy po partycjonowaniu.
				}
			}
		}

		//Wywolana jest partycja, uzyskany jest indeks pivota, 
		//Nastepnie dwie podtablice sa sortowane rekurencyjnie 
		void szybkie(int l, int h)
		{
			if (l >= h) return; // Warunek zakoñczenia rekurencji: jeœli lewy indeks jest wiêkszy lub równy prawemu, zakoñcz funkcjê.
			int x = partycja(l, h); // Wykonaj partycjonowanie tablicy, zwróæ indeks pivota.
			//Wywolanie funkcji dla lewej i prawej czesci tablicy 
			szybkie(l, x);
			szybkie(x + 1, h);
		}
};

#endif