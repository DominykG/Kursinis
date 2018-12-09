#pragma once
#include"GameState.h"
#include "CombatState.h"

enum encounters { EMPTY = 0, FARM, CITY, SHOP, CHEST, ALTAR };

//Visi meniu state'ai :D
class MainMenuState
	: public State
{
private:
	std::vector<Character*>* characterList;
	unsigned& activeCharacter;
	std::stack<State*>* states;

public:
	MainMenuState(
		std::vector<Character*>* characterList,
		unsigned& activeCharacter,
		std::stack<State*>* states);
	virtual ~MainMenuState();

	void printMenu();
	void updateMenu();
	void update();
	void loadGame();
};

class CharacterMenuState :
	public State
{
private:
	Character *& character;
	std::stack<State*>*states;

public:
	CharacterMenuState(Character*& character,
		std::stack<State*>* states);
	virtual ~CharacterMenuState();

	//Funkcijos

	void printMenu();
	void updateMenu();
	void update();
};

class CharacterStatMenuState :
	public State
{
private:
	Character *&character;
	std::stack<State*> *states;

public:
	CharacterStatMenuState(
		Character*& character,
		std::stack<State*>* states);
	virtual ~CharacterStatMenuState();

	//Funkcijos

	void printMenu();
	void updateMenu();
	void update();
};

class TravelMenuState :
	public State, Item
{
private:
	Character *& character;
	std::stack<State*>*states;
	std::string locationString;
	std::string minimapString;
	int nrOfLocations;
	int lootnr, RiddleAnswer, PlayerAnswer;
	int choice;
public:
	TravelMenuState(
		Character*& character,
		std::stack<State*>* states
		);
	virtual ~TravelMenuState();

	
	//Funkcijos

	void riddle();
	void printMenu();
	void updateEncounterMenu();
	void updateMinimap();
	void updateMenu();
	void update();
};

class CharacterCreatorState :
	public State
{
private:
	const unsigned maxCharacters;
	std::vector<Character*>* characterList;
	unsigned& activeCharacter;
	std::stack<State*>*states;

public:
	CharacterCreatorState(
		std::vector<Character*>* characterList,
		unsigned& activeCharacter,
		std::stack<State*>* states);
	virtual ~CharacterCreatorState();

	//Funkcijos
	void createCharacter();
	void printMenu();
	void updateMenu();
	void update();
};

class CharacterSelectorState :
	public State
{
private:
	std::vector<Character*>* characterList;
	unsigned& activeCharacter;
	std::stack<State*>* states;

public:
	CharacterSelectorState(
		std::vector<Character*>* characterList,
		unsigned& activeCharacter,
		std::stack<State*>* states);

	virtual ~CharacterSelectorState();

	//Funkcijos
	void loadCharacters();
	void printMenu();
	void updateMenu();
	void update();
};

class ShopMenuState
	: public State
{
private:
	int Desired_item;
	Character *& character;
	Inventory Shop_items;
	std::stack<State*>*states;

public:
	ShopMenuState(
		Character*& character,
		std::stack<State*>* states);
	virtual ~ShopMenuState();

	void printMenu();
	void updateMenu();
	void update();
};