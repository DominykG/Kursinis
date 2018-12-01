#include "Item.h"
#include<windows.h> 

//Private funkcijos 
void Item::generate()
{

} 

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
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	std::stringstream ss;

	std::cout << " Name: " << this->name
		<< " | Type: " << this->item_types[this->type]
		<< " | Rarity: ";
	switch (this->rarity)
	{
	case UNCOMMON:
		SetConsoleTextAttribute(Console, 0b00001010);
		std::cout << this->item_rarities[this->rarity];
		SetConsoleTextAttribute(Console, 0b00000111);
		break;

	case RARE:
		SetConsoleTextAttribute(Console, 0b00001001);
		std::cout << this->item_rarities[this->rarity];
		SetConsoleTextAttribute(Console, 0b00000111);
		break;

	case EPIC:
		SetConsoleTextAttribute(Console, 0b00001101);
		std::cout << this->item_rarities[this->rarity];
		SetConsoleTextAttribute(Console, 0b00000111);
		break;

	case LEGENDARY:
		SetConsoleTextAttribute(Console, 0b00001100);
		std::cout << this->item_rarities[this->rarity];
		SetConsoleTextAttribute(Console, 0b00000111);
		break;

	default:
		std::cout << this->item_rarities[this->rarity];
		break;
	}
	std::cout << " | Value: "; 

	SetConsoleTextAttribute(Console, 0b00001110);
	std::cout << this->value << "\n";
	SetConsoleTextAttribute(Console, 0b00000111);

	return ss.str();
}

int Item::saveItem()
{
	//saves only legit item 'look Item.h'
	//all custom items are *magicaly* turn into sticks
	return this->item_nr;
}
