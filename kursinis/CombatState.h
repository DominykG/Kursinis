#pragma once

#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stack>
#include "State.h"
#include "Character.h"
#include "Enemy.h"

class CombatState :
	public State
{
private:
	Character * & character;
	std::stack<State*>*states;

public:
	CombatState(Character*& character,
		std::stack<State*>*states);
	virtual ~CombatState();

	//Funkcijos
	void beginCombat();
	void printMenu();
	void updateMenu();
	void update();
};

