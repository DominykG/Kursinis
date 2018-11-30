#include "Item.h"

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
	std::stringstream ss;

	ss << " Name: " << this->name
		<< " | Type: " << this->type
		<< " | Rarity: " << this->rarity
		<< " | Value: " << this->value
		<< "\n";

	return ss.str();
}

int Item::saveItem()
{
	//saves only legit item 'look Item.h'
	//all custom items are *magicaly* turn into sticks
	return this->item_nr;
}
