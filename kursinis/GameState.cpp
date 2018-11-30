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
		<< gui::msg_menuitem(2, "Shop Menu.")
		<< gui::msg_menuitem(3, "Travel Menu.")
		<< gui::msg_menuitem(4, "Rest for a while.")
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
		this->states->push(new ShopMenuState(this->character, this->states)); // 2018-11-28
		break;

	case 3:
		this->states->push(new TravelMenuState(this->character, this->states));
		break;

	case 4:
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
	char answer;
	std::cout << "Do you want to save the game?(y/n) ";
	std::cin >> answer;

	if (answer == 'y')
	{
		std::cout << "Input save file name: ";
		std::string f_name1, f_name2;
		std::cin >> f_name1 >> f_name2;
		std::cout << f_name1 << f_name2;
		system("pause");

		std::ofstream fo;
		fo.open(f_name1 + f_name2 + ".save", std::ios::app);
		//saving character stats
		fo << this->character->Save_stats();
		//saving character inventory
		//saves 2 integers item in inventory position
		//and item index
		fo << this->character->getInventory().saveInventory();
		fo.close();
	}

}
