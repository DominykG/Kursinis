#pragma once

#include"Item.h"
#include<sstream>
#include<string>

class Inventory
{
private:
	Item **items;
	unsigned cap;
	unsigned nrOfItems;

	//Private funkcijos
	void initialize(const unsigned from = 0);
	void expand();

public:
	//Konstruktoriai ir dekonstruktoriai
	Inventory(unsigned cap = 10);
	Inventory(const Inventory& other);
	virtual ~Inventory();

	//Operatoriai darbui su pointeriais
	void operator = (const Inventory& other);
	Item& operator [] (const unsigned index);

	//Funkcjos gavimui private reiksmiu
	const unsigned& size() const;
	const unsigned& capacity() const;
	Item& at(const unsigned index);

	//Funkcijos
	void add(const Item& item);
	void remove(const unsigned index);
	std::string toString() const;
	std::string saveInventory() const;
};

/////////////////////////////////////////////////////////////////////////////////////////

class Weapon :
	public Item
{
private:
	int damageMax;
	int damageMin;

public:
	Weapon(
		int damageMin,
		int damageMax,
		std::string name,
		unsigned type,
		unsigned rarity,
		unsigned value);

	virtual ~Weapon();

	//Funkcija
};

/////////////////////////////////////////////////////////////////////////////////////////

class Armor :
	public Item
{
private:
	int defenceMax;
	int defenceMin;

public:
	Armor(
		int defenceMin,
		int defenceMax,
		std::string name,
		unsigned type,
		unsigned rarity,
		unsigned value);

	virtual ~Armor();

	//Funkcija
};
