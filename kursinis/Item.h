#pragma once

#include<string>
#include<sstream>

//currently using no dmg or defence items
enum item_types { WEAPON = 0, ARMOR };
enum item_rarities { COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY };
//looks like useless for now
enum items { STICK = 0, STONE, WOODEN_HAMMER, KNIFE,
		WOODEN_AXE, BOW, STEEL_AXE, STEEL_SWORD, ELVEN_BOW,
		EMERALD_SWORD, DRAGONBONE_SWORD, OBSIDIAN_SWORD, DIRTY_CLOTHES,
		LEATHER_ARMOR, CHAIN_ARMOR, IRON_ARMOR, STEEL_ARMOR,
		DRAGON_BONE_ARMOR, OBSIDIAN_ARMOR };

class Item
{
private:
	std::string name;
	unsigned type;
	unsigned rarity;
	unsigned value;
	int item_nr;
	void generate();
	//USE items enumerator to find item stats and item names or mb not?
	std::string item_names[19] = {"Stick", "Stone", "Wooden_Hammer", "Knife"
	"Wooden_Axe", "Bow", "Steel_Axe", "Steel_Sword", "Elven_Bow", 
	"Emerald_Bow", "Dragonbone_Sword", "Obsidian_Sword", "Dirty_Clothes", 
	"Leather_Armor", "Chain_Armor", "Iron_Armor", "Steel_Armor",
	"Dragonbone_Armor", "Obsidian_Armor"};
	///////////////////////////////////////////////////////////////////////////// 
	//item_stats[/*item*/][/*type, rarity, value*/];
	int item_stats[19][3] = { {WEAPON, COMMON, 1}, {WEAPON, COMMON, 1},
	{WEAPON, COMMON, 12}, {WEAPON, UNCOMMON, 50 }, {WEAPON, UNCOMMON, 90},
	{WEAPON, UNCOMMON, 240}, {WEAPON, RARE, 600}, {WEAPON, RARE, 1900},
	{WEAPON, EPIC, 5600}, {WEAPON, EPIC, 15000}, {WEAPON, LEGENDARY, 75000},
	{WEAPON, LEGENDARY, 100000},
	{ARMOR, COMMON, 1}, {ARMOR, UNCOMMON, 16}, {ARMOR, UNCOMMON, 150},
	{ARMOR, RARE, 600}, {ARMOR, EPIC, 2200}, {ARMOR, LEGENDARY, 5200},
	{ARMOR, LEGENDARY, 15000} };

public:
	Item(std::string name,
		unsigned type,
		unsigned rarity,
		unsigned value);
	Item(int);
	virtual ~Item();

	//Funkcjos gavimui private reiksmiu
	const std::string& getName();
	const unsigned& getType();
	const unsigned& getRarity();
	const unsigned& getValue();

	//Funkcijos
	const std::string toString() const;
	int saveItem();
};


