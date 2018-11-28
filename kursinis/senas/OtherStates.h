#pragma once

//#include "MenuStates.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stack>
#include "State.h"
#include "Character.h"
#include "Enemy.h"

//#include "CharacterMenuState.h"
//#include "TravelMenuState.h"

using namespace std;

class GameState :
	public State
{
private:
	Character *& character;
	stack<State*>*states;

public:
	GameState(Character*& character, stack<State*>*states);
	virtual ~GameState();

	//Functions
	void printMenu() const;
	void updateMenu();
	void update();
};

class CharacterCreatorState :
	public State
{
private:
	const unsigned maxCharacters;
	vector<Character*>* characterList;
	unsigned& activeCharacter;
	stack<State*>*states;

public:
	CharacterCreatorState(
		vector<Character*>* characterList,
		unsigned& activeCharacter,
		stack<State*>* states);
	virtual ~CharacterCreatorState();

	//Functions
	void createCharacter();
	void printMenu();
	void updateMenu();
	void update();
};

class CharacterSelectorState :
	public State
{
private:
	vector<Character*>* characterList;
	unsigned& activeCharacter;
	stack<State*>* states;

public:
	CharacterSelectorState(
		vector<Character*>* characterList,
		unsigned& activeCharacter,
		stack<State*>* states);

	virtual ~CharacterSelectorState();

	//Functions

	void printMenu();
	void updateMenu();
	void update();
};

class CombatState :
	public State
{
private:
	Character * & character;
	stack<State*>*states;

public:
	CombatState(Character*& character,
		stack<State*>*states);
	virtual ~CombatState();

	//Functions
	void beginCombat();
	void printMenu();
	void updateMenu();
	void update();
};

