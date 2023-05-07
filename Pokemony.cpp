#include <iostream>
#include <string> 

#include "Pokemon.h"
#include "Inventory.h"
#include "UI.h"

using namespace std;

int main()
{
	MainMenu menu = MainMenu();
	while (true)
	{
		InventoryMenu inventory = menu.moveToInventory();
		BattleField field = inventory.moveToBattlefield();
		Summary summary = field.moveToSummary(&menu.gamename);
	}
}
	