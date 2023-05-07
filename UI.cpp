#include "UI.h"
#include "Pokemon.h"
#include "Inventory.h"

using namespace std;

void UI::print()
{
    system("CLS");
    for (int y = 0; y < 30; y++)
    {
        for (int x = 0; x < 79; x++)
            cout << picture[x][y];
        cout << endl;
    }
}

void UI::help()
{
    system("CLS");
    
    cout << "W Menu Glownym:" << endl;
    cout << "1:[name] - utworz gre o podanej nazwie podanej jako [name]" << endl;
    cout << "2:[name] - wczytaj gre o podanej nazwie podanej jako [name]," <<endl <<"w przypadku braku pliku zapisu rozpocznij nowa gre" << endl;
    cout << "3 - opusc gre" << endl << endl;
    cout << "W Menu Ekwipunku:" << endl;
    cout << "[n] - dodaj pokemona o numerze podanym jako [n]" << endl << endl;
    cout << "Na polu bitwy:" << endl;
    cout << "ATC - zaatakuj przeciwnika" << endl;
    cout << "SPC - uzyj umiejetnosci specjalnej" << endl;
    cout << "SWC - zmien pokeman na nastepnego na stosie" << endl << endl;
    cout << "Na ekranie podumowania" << endl;
    cout << "1 - rozpocznij nastepna gre" << endl;
    cout << "2 - opusc gre" << endl << endl << endl;
    cout << "Wprowadz dowolna wartosc by kontynuowac" << endl;
    
    string x;
    cin >> x;
    print();
}

void UI::display(const string toDisplay, int x, const int y)
{
    for (char e : toDisplay)
    {
        picture[x][y] = e;
        x++;
    }
}

//##################################################################################### MainMenu

MainMenu::MainMenu()
{
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 79; x++)
        {
            picture[x][y] = ' ';
            if (y == 0 || y == 29)
                picture[x][y] = (char)205;
            if (x == 0 || x == 78)
                picture[x][y] = (char)186;
        }

    picture[0][0] = (char)201; // ╔
    picture[78][0] = (char)187; // ╗
    picture[0][29] = (char)200;  // ╚
    picture[78][29] = (char)188; // ╝

    display("1:[name] - START THE GAME", 29, 11);
    display("2:[name] - LOAD THE GAME", 29, 15);
    display("3 - EXIT", 37, 19);
    print();
    read();
}

void MainMenu::read()
{
    bool end = true;
    while (end)
    {
        end = false;
        string command;
        cin >> command;
        if (command == "-help")
        {
            help();
            end = true;
            continue;
        }

        char x = command.at(0);
        switch (x)
        {
            case '1':
                loaded = false;
                gamename = command.substr(2, command.length() - 2);
                break;
            case '2':
                gamename = command.substr(2, command.length() - 2);
                {
                    ifstream file;
                    file.open(command.substr(2, command.length() - 2)+".txt");
                    if (file)
                        loaded = true;
                    else
                        loaded = false;
                    file.close();
                }
                break;
            case '3':
                exit(0);
            default:
                print();
                end = true;
        }
        
    }
}

InventoryMenu MainMenu::moveToInventory()
{
    bool ret = loaded;
    loaded = true;
    return InventoryMenu(&gamename, ret);
}

//##################################################################################### Inventory
InventoryMenu::InventoryMenu(string* gameName, bool loaded)
{
    gamename = *gameName;
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 79; x++)
        {
            picture[x][y] = ' ';
            if (y == 0 || y == 29 || y==2)
                picture[x][y] = (char)205;
            if (x == 0 || x == 78 || x==39 && y>2)
                picture[x][y] = (char)186;
        }

    picture[0][0] = (char)201; // ╔
    picture[78][0] = (char)187; // ╗
    picture[0][29] = (char)200;  // ╚
    picture[78][29] = (char)188; // ╝

    picture[39][2] = (char)203; // ╦
    picture[39][29] = (char)202; // ╩

    picture[0][2] = (char)204; // ╠
    picture[78][2] = (char)185;// ╣

    display(loaded ? "Enter anything to continue" : "Choose your pokemons", 3, 1);
    
    for (int i = 0; i < 9; i++)
    {
        picture[41][4 + 2 * i] = '[';
        picture[42][4 + 2 * i] = (char)(i+49);
        picture[43][4 + 2 * i] = ']';
        display(pocket[i].giveInfo(), 45, 4 +2*i);
    }

    if (loaded)
    {
        inventory = Inventory(gamename);
        for (int j = 0; j < 5; j++)
        {
            picture[2][4 + 2 * j] = '[';
            picture[3][4 + 2 * j] = (char)(j + 49);
            picture[4][4 + 2 * j] = ']';
            display(inventory.givePok(j)->giveInfo(), 6, 4 + 2 * j);
            string toWrite = inventory.givePok(j)->giveInfo();
        }
    }
    print();
    if (!loaded) 
        read();
    string x;
    cin >> x;
}    

void InventoryMenu::read()
{
    inventory = Inventory();
    while (inventory.giveSize() < 5)
    {
        string command;
        cin >> command;
        if (command == "-help")
        {
            help();
            continue;
        }   
        
        if (command.length() == 1 && isdigit(command.at(0)) && command.at(0)!='0')
        {
            int input = stoi(command);
            inventory.add(pocket[input - 1]);
            inventory.numbers.push_back(input - 1);
            int j = inventory.giveSize() - 1;

            picture[2][4 + 2 * j] = '[';
            picture[3][4 + 2 * j] = (char)(j + 49);
            picture[4][4 + 2 * j] = ']';
            display(inventory.givePok(j)->giveInfo(), 6, 4 + 2 * j);
            print();
        }
        else 
            print();
    }
    inventory.save(&gamename);
    display("Enter anything to continue", 3, 1);
    print();
}

BattleField InventoryMenu::moveToBattlefield()
{
    return BattleField(inventory);
}
//##################################################################################### Battlefield
BattleField::BattleField(Inventory inv)
{
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 79; x++)
        {
            picture[x][y] = ' ';
            if (y == 0 || y == 29)
                picture[x][y] = (char)205;
            if (x == 0 || x == 78)
                picture[x][y] = (char)186;
            if (y == 19 || y == 3 || y == 21)
                picture[x][y] = (char)205;
            if (x == 39 && y > 19)
                picture[x][y] = (char)186;
        }

    picture[0][0] = (char)201; // ╔
    picture[78][0] = (char)187; // ╗
    picture[0][29] = (char)200;  // ╚
    picture[78][29] = (char)188; // ╝

    picture[0][3] = (char)204; // ╠
    picture[0][19] = (char)204; // ╠
    picture[0][21] = (char)204; // ╠

    picture[78][3] = (char)185;// ╣       
    picture[78][19] = (char)185;// ╣
    picture[78][21] = (char)185;// ╣ 

    picture[39][19] = (char)203; // ╦
    picture[39][29] = (char)202; // ╩

    picture[39][21] = (char)206; // ╬

    inventory1 = Inventory::copy(&inv);
    inventory2 = Inventory::generate(&inv);

    player = inventory1.givePok(0);
    opponent = inventory2.givePok(0);

    Wins1 = 0;
    Wins2 = 0;
    SWC1 = true;
    SWC2 = true;
    refreshStats();

    sendMassage("New Fight has begun");
    print();
    read();
}

void BattleField::sendMassage(const string a)
{
    for (int i = 3; i < 76; i++)
    {
        picture[i][1] = picture[i][2];
        picture[i][2] = ' ';
    }

    picture[3][2] = '-';
    display(a, 3, 2);
}

void BattleField::refreshStats()
{
    string name[2];
    name[0] = player->name + " LVL " + to_string(player->LVL) + "   ";
    name[1] = opponent->name + " LVL " + to_string(opponent->LVL) + "   ";
    for (int i = 0;i < 2;i++)
        display(name[i], 3 + i * 39, 20);

    string lines[10];
    lines[0] = "HP  " + to_string(player->HP) + '/' + to_string(player->MAXHP);
    while (lines[0].length() < 17)
        lines[0] += ' ';
    lines[0] += '|';
    for (int i = 0;i < 15;i++)
    {
        if(player->MAXHP!=0)
            if (player->HP * 15  / player->MAXHP > i)
                lines[0] += '#';
        else
            lines[0] += ' ';
    }
    lines[0] += '|';
    string ynSPC= player->SPC ? "YES" : "NO ";
    string ynSWC = SWC1 ? "YES" : "NO ";
    lines[1] = "STR  " + to_string(player->STR);
    lines[2] = "DEX  " + to_string(player->DEX);
    lines[3] = "SPC  " + ynSPC;
    lines[4] = "SWC  " + ynSWC;

    lines[5] = "HP  " + to_string(opponent->HP) + '/' + to_string(opponent->MAXHP);
    while (lines[5].length() < 17)
        lines[5] += ' ';
    lines[5] += '|';
    for (int i = 0;i < 15;i++)
    {
        if (opponent->HP  * 15/ opponent->MAXHP > i)
            lines[5] += '#';
        else
            lines[5] += ' ';
    }
    lines[5] += '|';
    ynSPC = opponent->SPC ? "YES" : "NO ";
    ynSWC = SWC2 ? "YES" : "NO ";
    lines[6] = "STR  " + to_string(opponent->STR);
    lines[7] = "DEX  " + to_string(opponent->DEX);
    lines[8] = "SPC  " + ynSPC;
    lines[9] = "SWC  " + ynSWC;

    for (int i = 0; i < 2; i++)
        display(lines[i * 4 + i], 3+i*39, 23);

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int w = 0; w < 2; w++)
                display(lines[i * 4 + i + 2 * j + w + 1], 3 + i * 39 + j * 17, 25 + w * 2);
}

void BattleField::read()
{
    while (Wins1 + Wins2 < 5 && abs(Wins1 - Wins2) < 3)
    {
        string command;
        cin >> command;
        if (command == "-help")
        {
            help();
            continue;
        }

        if (command == "ATC")
        {
            int hit = player->attack(opponent);
            sendMassage(hit == -1 ? "Player missed" : "Player has striked opponent with " + to_string(hit));
        }

        else if (command == "SPC")
        {
            player->spec(opponent);
            player->SPC = false;
            sendMassage("Player used special ability");
        }
            

        else if (command == "SWC" && SWC1)
        {
            player = inventory1.givePok((Wins1 + Wins2 + 1) % 5);
            SWC1 = false;
            sendMassage("Player has changed Pokemon");
            refreshStats();
            print();
            continue;
        }

        else
        {
            sendMassage("Error - wrong value");
            refreshStats();
            print();
            continue;
        }

        if(opponent->HP>0)
        {
            srand(time(NULL));
            if (opponent->SPC && rand() % 3 == 1)
            {
                opponent->spec(player);
                opponent->SPC = false;
                sendMassage("Opponent used special ability");
            }

            else if (SWC2 && rand() % 2 == 1 && opponent->giveEffect(player)==8)
            {
                opponent = inventory2.givePok((Wins1 + Wins2 + 1) % 5);
                SWC2 = false;
                sendMassage("Opponent has changed Pokemon");
            }
            else
            {
                int hit = opponent->attack(player);
                sendMassage(hit == -1 ? "Opponent missed" : "Opponent has striked player with " + to_string(hit));
            }
        }
        
        if (opponent->HP <= 0 || player->HP <= 0)
        {
            if (opponent->HP <= 0)
            {
                Wins1++;
                sendMassage("Player won the round");
            }
            else
            {
                Wins2++;
                sendMassage("Opponent won the round");
            }

            player = inventory1.givePok((Wins1 + Wins2)%5);
            opponent = inventory2.givePok((Wins1 + Wins2) % 5);
        }

        refreshStats();
        print();
    }
    sendMassage((Wins1 > Wins2) ? "Player won the game" : "Opponent won the game");
    sendMassage("Enter any value to continue");
    print();
    string x;
    cin >> x;
}


Summary BattleField::moveToSummary(const string* gameName)
{
    return Summary(inventory1, gameName);
}
//##################################################################################### Summary
Summary::Summary(Inventory data, const string* gameName)
{
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 79; x++)
        {
            picture[x][y] = ' ';
            if (y == 0 || y == 29 || y == 22 || y == 11)
                picture[x][y] = (char)205;
            if (x == 0 || x == 78 || (x == 26 || x==52) && y<22)
                picture[x][y] = (char)186;
        }

    picture[0][0] = (char)201; // ╔
    picture[78][0] = (char)187; // ╗
    picture[0][29] = (char)200;  // ╚
    picture[78][29] = (char)188; // ╝

    picture[0][22] = (char)204; // ╠
    picture[0][11] = (char)204; // ╠

    picture[78][22] = (char)185;// ╣ 
    picture[78][11] = (char)185;// ╣ 

    picture[26][0] = (char)203; // ╦
    picture[26][22] = (char)202; // ╩
    picture[52][0] = (char)203; // ╦
    picture[52][22] = (char)202; // ╩

    picture[26][11] = (char)206; // ╬
    picture[52][11] = (char)206; // ╬

    Inventory inventory = Inventory(*gameName);
    for (int i = 0; i < 5; i++)
    {
        Pokemon* toDisplay=data.givePok(i);
        Pokemon* toCompare = inventory.givePok(i);
        display(toDisplay->name, 3+(i%3)*26, (i<3)?1:12);
        display("LVL: " +   to_string(toCompare->LVL)+ "->" +to_string(toDisplay->LVL), 3 + (i % 3) * 26, (i < 3) ? 3 : 14);
        display("EXP: " + to_string(toCompare->EXP) + "->" + to_string(toDisplay->EXP), 3 + (i % 3) * 26, (i < 3) ? 5 : 16);
        display("STR: " + to_string(toCompare->STR) + "->" + to_string(toDisplay->STR), 3 + (i % 3) * 26, (i < 3) ? 7 : 18);
        display("DEX: " + to_string(toCompare->DEX) + "->" + to_string(toDisplay->DEX), 3 + (i % 3) * 26, (i < 3) ? 9 : 20);
    }
    
    data.save(gameName);
    display("1 - CONTINUE", 3, 24);
    display("2 - EXIT", 3, 27);
    print();
    read();
}

void Summary::read()
{
    bool end = true;
    while (end)
    {
        end = false;
        string command;
        cin >> command;
        if (command == "-help")
        {
            help();
            end = true;
            continue;
        }
        const char x = command.at(0);
        switch (x)
        {
        case '1':
            break;
        case '2':
            exit(0);
            break;
        default:
            print();
            end = true;
        }
    }
}