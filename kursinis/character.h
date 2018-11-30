#pragma once

#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<cmath>
#include"Inventory.h"

//(50/3) * (pow(x, 3) - 6*pow(x, 2) + (x * 17) - 12);

enum attributes { STRENGTH = 0, VITALITY, AGILITY, DEXTERITY, INTELLIGENCE };

class Character
{
private:
	//Zaidejo koordinates
	unsigned x;
	unsigned y;

	//Pagrindiniai personazo dalykai
	std::string name;
	
	int level;
	int exp;
	int expNext;
	int statpoints;

	//Stats
	int hp;
	int hpMax;
	int stamina; 
	int staminaMax;
	int mana;
	int manaMax;

	//atributai
	int strength; //Didina zala
	int vitality; //Didina  HP ir staminos max
	int agility; //Didina defence
	int dexterity; //Didina Pataikymo sansa ir krit chance
	int intelligence; //Didina max mana ir geresniu daiktu radimo %

	int damageMin;
	int damageMax;
	int defence;
	float hitRating;
	float critChance;
	float magicFind;

	int gold;

	//Skillai

	//Ginklas

	//Sarvai

	//Inventorius
	Inventory inventory;

	//Private funkcija
	void updateStats();

public:
	Character(std::string name);
	virtual ~Character();

	//Funkcjos gavimui private reiksmiu
	inline const int getSeed()  { return this->x + this->y; };
	inline const int getX()  { return this->x; }
	inline const int getY()  { return this->y; }
	inline const int getLevel() { return this->level; }
	inline const bool isDead()  { return this->hp <= 0; }
	inline const int getHP()   { return this->hp; }
	inline const int getHPMax()  { return this->hpMax; }
	inline const int getStamina()  { return this->stamina; }
	inline const int getDamageMin()  { return this->damageMin; }
	inline const int getDamageMax()  { return this->damageMax; }
	inline const int getDefence()  { return this->defence; }
	inline const int getHitRating()  { return this->hitRating; }
	inline Inventory& getInventory() { return this->inventory; }
	inline const int getGold() { return this->gold; } // 2018-11-28
	const int getAttribute(const unsigned attribute);

	//Funkcijos modifikuoti private reiksmes
	void setPosition(const unsigned x, const unsigned y);
	void move(const int x, const int y);

	//Funkcijos
	const std::string flee();
	void reset();
	void takeDamage(const int damage);
	void setDead();
	bool addExp(const int exp);
	bool addGold(const int gold);
	bool addStatpoint(const int attribute);
	const std::string getMenuBar(const bool show_attributes = false);
	const std::string toString();
	const std::string toStringPosition();
	const std::string toStringStats();

	const std::string Save_stats();
	//void Load_stats(std::ifstream& input);
};

