#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#include "Pokemon.h"

using namespace std;

class Inventory
{
	vector<Pokemon> pokemons;

	public:
		vector<int> numbers;
		Inventory();
		Inventory(const string filename);

		void add(Pokemon a); // dodaj pokemona na wierzch stosu
		void save(const string* gamename); // zapisz zestaw do pliku o nazwie gamename
		Pokemon* givePok(int pointer); // podaj pokemona z pod podanego adresu
		size_t giveSize() const; // podaj ilosc pokemonow na stosie
		static Inventory generate(Inventory* inv); // generuj przeciwnika do podanego zestawu inv
		static Inventory copy(Inventory* inv); // skopiuj zestaw
};

