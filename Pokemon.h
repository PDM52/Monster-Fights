#pragma once
#include <string> 
#include <functional>

using namespace std;

enum Type
{
	WAT = 0, EAR = 1, AIR = 2, FIR = 3, ICE = 4, STE = 5
};

class Pokemon
{
	const int effectivity[6][6] = { {8,8,10,8,10,10}, {10,10,8,12,12,12}, {10,8,10,10,12,8}, {8,8,10,10,12,12}, {8,12,10,8,8,10}, {12,10,12,8,10,8} };
	public:
		string name;
		int HP, MAXHP, EXP, STR, DEX, LVL;
		bool SPC;
		int sprite[4];
		Type type;
		function<void(Pokemon*)> spec;

		Pokemon(string a, int b, int c, int d, Type f, function<void(Pokemon*)> g);

		int giveEffect(Pokemon* a); // zwraca modyfikator obrazen przeciwko pokemonowi A
		int attack(Pokemon* a);  // jeœli DEX pokemona A jest ni¿sze ni¿ losowa liczba z przedzia³u od 0 do 100 zadaj mu obra¿enia z przedzia³u od 85% STR do 115% STR zmodyfikowana o efektywnosc i zwróæ t¹ wartoœæ, wpw zwróæ -1
		bool grantEXP(int a); // // dodaj A punktów EXP i sprawdŸ czy osi¹gniêto limit dla danego poziomu, jeœli tak podnieœ poziom o 1 i ponownie wywowaj t¹ funkcjê, oraz zwróæ true, 
          // jeœli poziom nie zosta³ zmieniony zwróæ false
		void levelUP(int i); // podnieœ poziom i razy zwiêkszaj¹c odpowiednio atrybuty HP, STR i DEX
		string giveInfo() const; // podaj informacje o pokemonie w formie stringa jako <name> <LVL> | <HP> | <STR> | <DEX>
};

static Pokemon pocket[9] =
{
	Pokemon(Pokemon("Petamon", 12, 8, 4, Type::WAT, [](Pokemon* a) { a->HP = a->HP / 2;})),
	Pokemon(Pokemon("Metamon", 6, 9, 3, Type::FIR, [](Pokemon* a) { a->STR = 2;})),
	Pokemon(Pokemon("Alfred", 4, 15, 5, Type::STE, [](Pokemon* a) { a->HP = 5;})),
	Pokemon(Pokemon("Ikamon", 4, 8, 7, Type::ICE, [](Pokemon* a) { a->HP = a->HP / 3 + 2;})),
	Pokemon(Pokemon("Terpamon", 4, 12, 7, Type::AIR, [](Pokemon* a) { a->HP = 8;})),
	Pokemon(Pokemon("Andrzej", 8, 1, 1, Type::WAT, [](Pokemon* a) { a->HP = 1; a->DEX += 10;})),
	Pokemon(Pokemon("Ratomon", 20, 3, 2, Type::FIR, [](Pokemon* a) { a->DEX = 0;})),
	Pokemon(Pokemon("Izimon", 4, 12, 7, Type::ICE, [](Pokemon* a) { a->DEX = 2; a->STR = 2; a->HP = a->HP * 2;})),
	Pokemon(Pokemon("Eletromon", 6, 7, 10, Type::AIR, [](Pokemon* a) { a->HP = a->HP = 2; a->STR = 10;}))
};