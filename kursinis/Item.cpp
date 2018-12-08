#include "Item.h"
#include<iomanip>

//Private funkcijos 


//Konstruktoriai ir dekonstruktoriai
Item::Item(
	std::string name,
	unsigned type,
	unsigned rarity,
	unsigned value
)
{
	this->name = name;
	this->type = type;
	this->rarity = rarity;
	this->value = value;
	this->item_nr = 0;
}

Item::Item(int item) : item_nr(item)
{
	this->name = item_names[item];
	this->type = item_stats[item][0];
	this->rarity = item_stats[item][1];
	this->value = item_stats[item][2];
}

Item::~Item()
{

}

//Funkcjos gavimui private reiksmiu
const std::string & Item::getName()
{
	return this->name;
}

const unsigned & Item::getType()
{
	return this->type;
}

const unsigned & Item::getRarity()
{
	return this->rarity;
}

const unsigned & Item::getValue()
{
	return this->value;
}

//Funkcijos
const std::string Item::toString() const
{
	//color change dont work in these conditions 
	//HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	std::stringstream ss;

	ss << "  Name: " << this->name
		<< "  | Type: " << this->item_types[this->type]
		<< "  | Rarity: " << this->item_rarities[this->rarity]
		<< "  | Value: " << this->value << "\n";
	return ss.str();
}

int Item::saveItem()
{
	//saves only legit item 'look Item.h'
	//all custom items are *magicaly* turn into sticks
	return this->item_nr;
}

int Item::generate()
{
	srand(time(NULL));
	int randomnr = rand() % 1000 + 1;
	int lootType, lootNr;
	lootType = rand() % 2;
	if (randomnr >=0 && randomnr <= 30){ //Legendary 3%

		if (lootType == 0)
			lootNr = rand() % 2 + 10;
		else
			lootNr = rand() % 2 + 17;
		return lootNr;
	}
	else if (randomnr >= 31 && randomnr <=100 ) { //Epic 7%

		if (lootType == 0)
			lootNr = rand() % 2 + 8;
		else 
			lootNr = 16;
		return lootNr;
	}
	else if (randomnr >= 101 && randomnr <= 300) { //Rare 20%

		if (lootType == 0)
			lootNr = rand() % 2 + 6;
		else
			lootNr = 15;
		return lootNr;
	}
	else if (randomnr >= 301 && randomnr <= 600) { //Unc 30%

		if (lootType == 0)
			lootNr = rand() % 3 + 3;
		else
			lootNr = rand() % 2 + 13;
		return lootNr;
	}
	else if (randomnr >= 601 && randomnr <= 1000) { //Com 40%

		if (lootType == 0)
			lootNr = rand() % 3;
		else
			lootNr = 12;
		return lootNr;
	}
	
}