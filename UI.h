#pragma once
#include <string> 
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#include "Pokemon.h"
#include "Inventory.h"

class UI
{
    protected:
        char picture[79][30];
    public:
        void print(); // wyswietl obraz przechowywany w picture
        void help(); // wyswietl pomoc
        void display(const string toDisplay, int x, const int y); // zaladuj toDisplay do wyswitlenia po x-tym znaku y lini
};

class Summary :UI
{
    public: 
        Summary(Inventory data, const string* gameName);
        void read(); // odczytaj i zinterpretuj podana przez uzytkownika komende
};

class BattleField :UI
{
    Pokemon* player; 
    Pokemon* opponent;
    Inventory inventory1, inventory2;
    bool SWC1, SWC2;
    int Wins1, Wins2;
    public:
        BattleField(Inventory inv);
        void sendMassage(const string a); // zaladuj do wyswietlnia w gornej czessci okna wiadomosc a
        void refreshStats(); // odswierz wszystkie statystyki obydwu graczy
        void read(); // odczytaj i zinterpretuj podana przez uzytkownika komende
        Summary moveToSummary(const string* gamename); // utworz ekran Summary i przekaz mu wszystkie niezbedne informacje, wlaczajac ogolna znazwe gry - gamename
};

class InventoryMenu :public UI
{
    Inventory inventory;
    string gamename;
    public:
        InventoryMenu(string *gameName, bool loaded);
        void read(); // odczytaj i zinterpretuj podana przez uzytkownika komende
        BattleField moveToBattlefield(); // utworz ekran Battlefield i przekaz mu wszystkie niezbedne informacj
};

class MainMenu :UI
{
    bool loaded;
    public:
        string gamename;
        MainMenu();
        void read(); // odczytaj i zinterpretuj podana przez uzytkownika komende
        InventoryMenu moveToInventory(); // utworz ekran InventoryMenu i przekaz mu wszystkie niezbedne informacj
};
