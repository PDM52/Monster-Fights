#include "Inventory.h"

Inventory::Inventory() = default;

Inventory::Inventory(const string filename)
{
	ifstream file;
	file.open(filename + ".txt");

	for (string line; getline(file, line); )
	{
		Pokemon toAdd = pocket[(int)line.at(0)-48];
		toAdd.levelUP((int)line.at(1)-49);
		toAdd.grantEXP(stoi(line.substr(2, line.length() - 2)));
		add(toAdd);
		numbers.push_back((int)line.at(0) - 49);
	}
}

Inventory Inventory::generate(Inventory* inv)
{
	int sum=0;
	for (int i = 0; i < 5;i++)
		sum += inv->givePok(i)->LVL;
	Inventory ret = Inventory();
	for (int i = 0; i < 5; i++)
	{
		srand(time(NULL));
		Pokemon pok = pocket[rand() % 9];
		pok.levelUP(sum/5);
		ret.add(pok);
	}
	return ret;
}

Inventory Inventory::copy(Inventory* inv)
{
	Inventory ret = Inventory();
	for (int i = 0; i < 5; i++)
	{
		Pokemon* pok = inv->givePok(i);
		ret.add(*pok);
	}
	for(int n : inv->numbers)
		ret.numbers.push_back(n);
	return ret;
}

void Inventory::add(Pokemon a)
{
	pokemons.push_back(a);
}

void Inventory::save(const string* gamename)
{
	ofstream out(*gamename + ".txt");
	for (int i = 0; i < 5; i++)
	{
		out << numbers[i];
		out << givePok(i)->LVL;
		out << givePok(i)->EXP;
		out << endl;
	}
	out.close();
}

Pokemon* Inventory::givePok(int a)
{
	return &pokemons[a];
}

size_t Inventory::giveSize() const
{
	return pokemons.size();
}