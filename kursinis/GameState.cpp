#include "GameState.h"

GameState::GameState(
	Character*& character,
	std::stack<State*>*states)
	: State(), character(character)
{
	this->states = states;
}

GameState::~GameState()
{

}

//Funkcijos
void GameState::printMenu() 
{
	system("CLS");
	std::cout << gui::msg_menutitle("Game Menu");

	std::cout << this->character->getMenuBar();

	std::cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Quit to main menu.")
		<< gui::msg_menuitem(1, "Character Menu.")
		<< gui::msg_menuitem(2, "Travel Menu.")
		<< gui::msg_menuitem(3, "Rest for a while.")
		<< gui::msg_menudivider(40, '-');
}

void GameState::updateMenu()
{
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;

	case 1:
		this->states->push(new CharacterMenuState(this->character, this->states));
		break;

	case 2:
		this->states->push(new TravelMenuState(this->character, this->states));
		break;

	case 3:
		system("cls");
		this->character->reset();
		// save me padaryk
		this->saveCharacter();

		std::cout << "You have rested..." << "\n";
		system("pause");
		break;

	default:
		system("CLS");
		std::cout << "Not a valid option!" << "\n";
		system("PAUSE");
		break;
	}
}

void GameState::update()
{
	//spausdint meniu
	this->printMenu();

	//Paimti pasirinkima gavus tinkama
	this->updateMenu();
}

void GameState::saveCharacter()
{
	std::string answer;
	std::cout << "Do you want to save the game?(y/n) ";
	std::getline(std::cin, answer);

	if (answer == "y")
	{
		std::string f_name;
		std::ofstream fo;
		std::cout << "Input save file name: ";
		std::getline(std::cin, f_name);

		fo.open(f_name + ".save");
		//saving character stats
		fo << this->character->Save_stats();
		//saving character inventory
		//saves 2 integers item in inventory position
		//and item index
		fo << this->character->getInventory().saveInventory();
		fo.close();
	}

}
