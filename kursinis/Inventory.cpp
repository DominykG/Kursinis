#include "Inventory.h"

//Private funkcijos

void Inventory::initialize(const unsigned from)
{
	for (size_t i = from; i < this->cap; i++)
	{
		this->items[i] = nullptr;
	}
}

void Inventory::expand()
{
	this->cap *= 2;

	Item** temp = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		temp[i] = this->items[i];
	}

	delete[] this->items;

	this->items = temp;

	this->initialize(this->nrOfItems);
}

//Konstruktoriai ir dekonstruktoriai
Inventory::Inventory(unsigned cap)
{
	this->cap = cap;
	this->nrOfItems = 0;
	this->items = new Item*[cap];

	this->initialize();
}

Inventory::Inventory(const Inventory& other)
{
	this->cap = other.cap;
	this->nrOfItems = other.nrOfItems;

	this->items = new Item*[this->cap];

	this->initialize();

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		this->items[i] = new Item(*other.items[i]);
	}
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		delete this->items[i];
	}

	delete[] this->items;
}

//Operatoriai darbui su stringais
void Inventory::operator=(const Inventory& other)
{
	if (this != &other)
	{
		for (size_t i = 0; i < this->nrOfItems; i++)
		{
			delete this->items[i];
		}
		delete[] this->items;

		this->cap = other.cap;
		this->nrOfItems = other.nrOfItems;

		this->items = new Item*[this->cap];

		this->initialize();

		for (size_t i = 0; i < this->nrOfItems; i++)
		{
			this->items[i] = new Item(*other.items[i]);
		}
	}
}

Item& Inventory::operator[](const unsigned index)
{
	if (index < 0 || index >= this->nrOfItems)
	{
		throw("OUT OF BOUNDS!");
	}

	return *this->items[index];
}

//Funkcjos gavimui private reiksmiu
const unsigned & Inventory::size() const
{
	return this->nrOfItems;
}

const unsigned & Inventory::capacity() const
{
	return this->cap;
}

Item & Inventory::at(const unsigned index)
{
	if (index < 0 || index >= this->nrOfItems)
	{
		throw("OUT OF BOUNDS!");
	}

	return *this->items[index];
}

//Funkcijos
void Inventory::add(const Item & item)
{
	if (this->nrOfItems >= this->cap)
		this->expand();

	this->items[this->nrOfItems++] = new Item(item);
}


void Inventory::remove(const unsigned index)
{
	//2018-11-28
	delete this->items[index];
		for (int i =index; i< nrOfItems-1; i++)
		{
			this->items[i] = this->items[i + 1];
		}
		nrOfItems--;
}

std::string Inventory::toString() const
{
	std::stringstream ss;

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		ss << i << ":  " << this->items[i]->toString() << "\n";
	}

	return ss.str();
}

std::string Inventory::saveInventory() const
{
	std::stringstream ss;
	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		ss << " " << this->items[i]->saveItem();
	}
	return ss.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Weapon::Weapon(
	int damageMin,
	int damageMax,
	std::string name,
	unsigned type,
	unsigned rarity,
	unsigned value)
	: Item(name, type, rarity, value)
{
	this->damageMax = damageMax;
	this->damageMin = damageMin;
}

Weapon::~Weapon()
{

}


//Funkcijos

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Armor::Armor(
	int defenceMin,
	int defenceMax,
	std::string name,
	unsigned type,
	unsigned rarity,
	unsigned value)
	: Item(name, type, rarity, value)
{
	this->defenceMax = defenceMax;
	this->defenceMin = defenceMin;
}

Armor::~Armor()
{

}