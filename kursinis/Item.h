#pragma once

#include<string>
#include<sstream>

enum item_types { WEAPON = 0, ARMOR };
enum item_rarities { COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY };

class Item
{
private:
	std::string name;
	unsigned type;
	unsigned rarity;
	unsigned value;

	void generate();

public:
	Item(std::string name,
		unsigned type,
		unsigned rarity,
		unsigned value);
	virtual ~Item();

	//Funkcjos gavimui private reiksmiu
	const std::string& getName();
	const unsigned& getType();
	const unsigned& getRarity();
	const unsigned& getValue();

	//Funkcijos
	const std::string toString() const;
};


