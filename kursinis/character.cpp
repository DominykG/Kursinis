#include "Character.h"

//Private funkcijos
void Character::updateStats()
{
	this->hpMax = this->attributes[VITALITY] * 10 + this->attributes[VITALITY];
	this->hp = this->hpMax;
	this->staminaMax = this->attributes[VITALITY] * 2;
	this->stamina = this->staminaMax;
	this->manaMax = this->attributes[VITALITY] * 10 + this->attributes[VITALITY];
	this->mana = this->manaMax;

	this->damageMin = this->attributes[STRENGTH] * 2;
	this->damageMax = this->attributes[STRENGTH] + this->attributes[STRENGTH] * 2;
	this->defence = this->attributes[AGILITY] * 2;
	this->hitRating = this->attributes[DEXTERITY] * 2 + this->attributes[DEXTERITY];
	this->critChance = static_cast<float>(this->attributes[DEXTERITY]) / 60;
	this->magicFind = static_cast<float>(this->attributes[INTELLIGENCE]) / 70;
}
//Konstruktoriai ir dekonstruktoriai
Character::Character(std::string name)
{
	this->x = 0;
	this->y = 0;

	this->name = name;
	
	this->level = 1;
	this->exp = 0;
	this->expNext = 46;
	this->statpoints = 5;

	this->attributes[STRENGTH] = 1;
	this->attributes[VITALITY] = 1;
	this->attributes[AGILITY] = 1;
	this->attributes[DEXTERITY] = 1;
	this->attributes[INTELLIGENCE] = 1;

	this->gold = 100; // for debug purposes

	this->updateStats();

	this->inventory.add(Item(0));
	this->inventory.add(Item(1));
	this->inventory.add(Item(2));
	this->inventory.add(Item(3));
	this->inventory.add(Item(4));
	this->inventory.add(Item(5));
	this->inventory.add(Item(6));
	this->inventory.add(Item(7));
}
//constructor for loading saved character
Character::Character()
{
	this->expNext = 46;

	int item;

	std::ifstream fi;
	std::string f_name;

	while (true)
	{
		std::system("cls");
		std::cout << "Input save file name: "; 
		std::getline(std::cin, f_name);


		fi.open(f_name + ".save");

		if (fi.is_open())
		{
			fi >> this->x >> this->y >> this->name
				>> this->level >> this->exp >> this->statpoints;

			for (int i = 0; i <= 4; i++)
			{
				fi >> this->attributes[i];
			}

			fi >> this->gold;

			this->updateStats();

			while (!fi.eof())
			{
				fi >> item;
				this->inventory.add(Item(item));
			}
			break;
		}

	}
	std::system("pause");
}

Character::~Character()
{

}

//Funkcjos gavimui private reiksmiu
const int Character::getAttribute(const unsigned attribute)
{
	return this->attributes[attribute];
}

//Funkcijos modifikuoti private reiksmes
void Character::setPosition(const unsigned x, const unsigned y)
{
	this->x = x;
	this->y = y;
}

void Character::move(const int x, const int y)
{
	if (static_cast<int>(this->x) + x < 0)
		this->x = 0;
	else
		this->x += x;

	if (static_cast<int>(this->y) + y < 0)
		this->y = 0;
	else
		this->y += y;
}

//Funkcijos
const std::string Character::flee()
{
	std::stringstream ss;
	int lostExp = rand() % (this->level * 5) + 1;
	int lostGold = rand() % (this->level * 5) + 1;
	ss << " Exp lost: " << lostExp << " | " << " Gold lost: " << lostGold;

	this->exp -= lostExp;;

	if (this->exp < 0)
		this->exp = 0;

	this->gold -= lostGold;

	if (this->gold < 0)
		this->gold = 0;

	return ss.str();
}

void Character::reset()
{
	this->hp = this->hpMax;
	this->stamina = this->staminaMax;
	this->mana = this->manaMax;
}

void Character::takeDamage(const int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
		this->setDead();
		
	
}

void Character::setDead()
{
	this->hp = 0;

	//Pagalvoti gal dar kokiu veiksmu pvz prikelti zaideja 
	this->exp -= rand() % (this->level * 10) + 1;

	if (this->exp < 0)
		this->exp = 0;

	this->gold -= rand() % (this->level * 10) + 1;

	if (this->gold < 0)
		this->gold = 0;
}

bool Character::addExp(const int exp)
{
	bool levelup = false;

	this->exp += exp;

	while (this->exp >= this->expNext)
	{
		this->level++;
		this->exp -= this->expNext;
		this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
		this->statpoints++;

		this->attributes[STRENGTH] += this->level % 2;
		this->attributes[VITALITY] += this->level % 2;
		this->attributes[AGILITY] += this->level % 2;
		this->attributes[DEXTERITY] += this->level % 2;
		this->attributes[INTELLIGENCE] += this->level % 2;

		this->updateStats();
		levelup = true;
	}

	//this->updateStats();

	return levelup;
}

bool Character::addGold(const int gold)
{
	this->gold += gold;
	return true;
	
}

bool Character::addStatpoint(const int attribute)
{
	if (this->statpoints > 0 && attribute >= 0 && attribute <= 4)
	{
		this->statpoints--;

		this->attributes[attribute]++;

		this->updateStats();

		return true;
	}

	return false;
}

const std::string Character::getMenuBar(const bool show_attributes)
{
	std::stringstream ss;

	int expDone = 10 * (static_cast<float>(this->exp) / this->expNext);
	int expRemain = 10 - expDone;

	ss
		<< std::string(4, ' ') << " | Name: " << this->name << "\n"
		<< std::string(4, ' ') << " | Level: " << this->level << " [" << std::string(expDone, '=') << std::string(expRemain, '-') << "]" << "\n"
		<< std::string(4, ' ') << " | HP: " << this->hp << " / " << this->hpMax << "\n"
		<< std::string(4, ' ') << " | Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< std::string(4, ' ') << " | Stat points available: " << this->statpoints << "\n";

	if (show_attributes)
	{
		ss << "\n";
		for (int i = 0; i <= 4; i++)
		{
			ss << std::string(4, ' ') << " |" << this->attribute_names[i] << this->attributes[i] << "\n";
		}
	}

	ss << "\n";

	return ss.str();
}

const std::string Character::toString()
{
	/* Function will format all member variables and
	send them out as a string to be printed.
	*/

	std::stringstream ss;

	ss << " Name: " << this->name << "\n" << "\n"
		<< " Level: " << this->level << "\n"
		<< " Exp: " << this->exp << " / " << this->expNext << "\n"
		<< "\n";

	for (int i = 0; i <= 4; i++)
	{
		ss << this->attribute_names[i] << this->attributes[i] << "\n";
	}

	ss << "\n HP: " << this->hp << " / " << this->hpMax << "\n"
		<< " Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< " Mana: " << this->mana << " / " << this->manaMax << "\n"
		<< "\n"

		<< " Damage: " << this->damageMin << " - " << this->damageMax << "\n"
		<< " Defence: " << this->defence << "\n"
		<< " Hit rating: " << this->hitRating << "\n"
		<< " Crit chance: " << this->critChance << "\n"
		<< " Magic find: " << this->magicFind << "\n"
		<< "\n"

		<< " Gold: " << this->gold << "\n"
		<< "\n";

	return ss.str();
}

const std::string Character::toStringPosition()
{
	std::stringstream ss;

	ss << " x: " << this->x << " y: " << this->y << "\n";

	return ss.str();
}

const std::string Character::toStringStats()
{
	std::stringstream ss;

	ss << " Level: " << this->level << "\n"
		<< " Exp: " << this->exp << " / " << this->expNext << "\n"
		<< "\n";

	for (int i = 0; i <= 4; i++)
	{
		ss << this->attribute_names[i] << this->attributes[i] << "\n";
	}

	ss << "\n HP: " << this->hp << " / " << this->hpMax << "\n"
		<< " Stamina: " << this->stamina << " / " << this->staminaMax << "\n"
		<< " Mana: " << this->mana << " / " << this->manaMax << "\n"
		<< "\n"

		<< " Damage: " << this->damageMin << " - " << this->damageMax << "\n"
		<< " Defence: " << this->defence << "\n"
		<< " Hit rating: " << this->hitRating << "\n"
		<< " Crit chance: " << this->critChance << "\n"
		<< " Magic find: " << this->magicFind << "\n"
		<< "\n"

		<< " Gold: " << this->gold << "\n"
		<< "\n";

	return ss.str();
}

const std::string Character::Save_stats()
{
	std::stringstream ss;

	ss << this->x << " " << this->y
		<< " " << this->name
		<< " " << this->level
		<< " " << this->exp
		<< " " << this->statpoints
		<< std::endl;//attributes

	for (int i = 0; i <= 4; i++)
	{
		ss << this->attributes[i] << " ";
	}

	ss << "\n" << this->gold << std::endl;

	return ss.str();
}