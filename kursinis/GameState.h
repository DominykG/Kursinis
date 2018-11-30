#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stack>
//#include<string>
#include "State.h"
#include "Character.h"
#include "Enemy.h"
#include "MenuStates.h"

class GameState :
	public State
{
private:
	Character *& character;
	std::stack<State*>*states;

public:
	GameState(Character*& character, std::stack<State*>*states);
	virtual ~GameState();

	//Funkcijos
	void printMenu();
	void updateMenu();
	void update();
	void saveCharacter();
};

