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
