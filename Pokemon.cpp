#include "Pokemon.h"
#include <time.h> 
#include <stdlib.h>
#include <string> 


Pokemon::Pokemon(string a, int b, int c, int d, Type f, function<void(Pokemon*)> g)
{
    name = a;
    MAXHP = b;
    HP = MAXHP;
    STR = c;
    DEX = d;
    LVL = 1;
    EXP = 0;
    type = f;
    spec = g;
    SPC = true;
}

int Pokemon::giveEffect(Pokemon* a)
{
    return effectivity[type][a->type];
}

int Pokemon::attack(Pokemon* a)
{
    srand(time(NULL));
    if (a->DEX < rand() % 100)
    {
        int damage = STR;
        a->HP -= damage;
        grantEXP(damage * 10);
        return damage;
    }
    return -1;
}

bool Pokemon::grantEXP(int a)
{
    EXP += a;
    if (EXP > pow(LVL, 2) * 100 && LVL < 9)
    {
        levelUP(1);
        EXP -= pow(LVL - 1, 2) * 100;
        grantEXP(0);
        return true;
    }
    return false;
}

void Pokemon::levelUP(int i)
{
    for (; i > 0; i--)
    {
        LVL++;
        MAXHP += 20 + LVL / 4 * 10;
        HP += 20 + LVL / 4 * 10;
        STR += STR * 0.2;
        DEX += 2;;
    }
}

string Pokemon::giveInfo() const
{
    return name + " " + to_string(LVL) + " |HP " + to_string(HP) + "|STR " + to_string(STR) + "|DEX " + to_string(DEX);
}