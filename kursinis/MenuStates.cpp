#include "MenuStates.h"


MainMenuState::MainMenuState(
	std::vector<Character*>* characterList,
	unsigned& activeCharacter,
	std::stack<State*>* states)
	: State(), activeCharacter(activeCharacter)
{
	this->characterList = characterList;
	this->states = states;

	//Debbuginimui
	this->characterList->push_back(new Character("TEST"));
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::printMenu()
{
	system("CLS");
	std::cout << gui::msg_menutitle("Main Menu");

	if (!this->characterList->empty())
		std::cout << this->characterList->at(this->activeCharacter)->getMenuBar();
	else
		std::cout << gui::msg_error("No character selected.");

	std::cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Quit to desktop. ")
		<< gui::msg_menuitem(1, "Start game. ")
		<< gui::msg_menuitem(2, "Create character. ")
		<< gui::msg_menuitem(3, "Select character. ")
		<< gui::msg_menuitem(4, "Load character. ")
		<< gui::msg_menudivider(40, '-');
}

void MainMenuState::updateMenu()
{
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;
	case 1:
		if (!this->characterList->empty())
			this->states->push(new GameState(this->characterList->at(this->activeCharacter), this->states));
		else
		{
			system("CLS");
			std::cout << "  [[ (!) Error. Create a character first. ]]" << "\n";
			system("PAUSE");
		}
		break;
	case 2:
		this->states->push(new CharacterCreatorState(this->characterList, this->activeCharacter, this->states));
		break;
	case 3:
		this->states->push(new CharacterSelectorState(this->characterList, this->activeCharacter, this->states));
		break;
	case 4:
		this->loadGame();
		break;
	default:
		system("CLS");
		std::cout << "  [[ (!) Not a valid option. ]]" << "\n";
		system("PAUSE");
		break;
	}
}

//Funkcijos
void MainMenuState::update()
{
	this->printMenu();
	this->updateMenu();
}

void MainMenuState::loadGame()
{
	this->characterList->push_back(new Character());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterMenuState::CharacterMenuState(
	Character*& character,
	std::stack<State*>* states)
	: character(character), State()
{
	this->states = states;
}

CharacterMenuState::~CharacterMenuState()
{

}

//Fuunkcijos
void CharacterMenuState::printMenu()
{
	system("CLS");
	std::cout << gui::msg_menutitle("Character Menu");

	std::cout << this->character->getMenuBar();

	std::cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Back to menu.")
		<< gui::msg_menuitem(1, "Stats.")
		<< gui::msg_menuitem(2, "Assign statpoints.")
		<< gui::msg_menuitem(3, "Inventory.")
		<< gui::msg_menudivider(40, '-');
}

void CharacterMenuState::updateMenu()
{
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;
	case 1:
		system("CLS");
		std::cout << this->character->toStringStats() << "\n";
		system("PAUSE");
		break;
	case 2:
		this->states->push(new CharacterStatMenuState(this->character, this->states));
		break;
	case 3:
		system("CLS");
		std::cout << this->character->getInventory().toString() << "\n";
		system("PAUSE");
		break;
	default:
		system("CLS");
		std::cout << gui::msg_error("Not a valid option.");
		system("PAUSE");
		break;
	}

}

void CharacterMenuState::update()
{
	this->printMenu();
	this->updateMenu();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterStatMenuState::CharacterStatMenuState(
	Character*& character,
	std::stack<State*>* states)
	: character(character), State()

{
	this->states = states;
}

CharacterStatMenuState::~CharacterStatMenuState()
{

}

void CharacterStatMenuState::printMenu()
{
	system("CLS");
	std::cout << gui::msg_menutitle("Statpoint Menu");

	std::cout << this->character->getMenuBar(true);

	std::cout << gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Quit to menu")
		<< gui::msg_menuitem(1, "Strength")
		<< gui::msg_menuitem(2, "Vitality")
		<< gui::msg_menuitem(3, "Agility")
		<< gui::msg_menuitem(4, "Dexterity")
		<< gui::msg_menuitem(5, "Intelligence")
		<< gui::msg_menudivider(40, '-');
}

void CharacterStatMenuState::updateMenu()
{
	int choice = this->getChoice();

	if (choice == -1)
	{
		this->setQuit(true);
	}
	else if (choice >= 1 && choice <= 5)
	{
		if (!this->character->addStatpoint(choice - 1))
			std::cout << gui::msg_error("Not enough statpoints.");
	}
	else
	{
		system("CLS");
		std::cout << gui::msg_error("Not a valid option.");
		system("PAUSE");
	}
}

//Funkcijos
void CharacterStatMenuState::update()
{
	this->printMenu();
	this->updateMenu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TravelMenuState::TravelMenuState(
	Character*& character,
	std::stack<State*>* states)
	: character(character), State()
{
	this->states = states;
	this->locationString = "NONE";
	this->nrOfLocations = 5;
}

TravelMenuState::~TravelMenuState()
{

}

//Funkcijos

void TravelMenuState::printMenu()
{
	system("CLS");
	std::cout << gui::msg_menutitle("Travel Menu");

	std::cout
		<< this->character->getMenuBar();

	std::cout
		<< "\n"
		<< std::string(4, ' ') << this->character->toStringPosition()
		<< "\n"
		<< std::string(4, ' ') << "Location: " << this->locationString << "\n"
		<< "\n"
		<< std::string(4, ' ') << "Minimap: " << "\n" << this->minimapString << "\n";

	std::cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Back to menu")
		<< gui::msg_menuitem(1, "UP")
		<< gui::msg_menuitem(2, "DOWN")
		<< gui::msg_menuitem(3, "LEFT")
		<< gui::msg_menuitem(4, "RIGHT")
		<< gui::msg_menuitem(5, "Restore your health "); //2018-11-28
}

void TravelMenuState::updateEncounterMenu()
{
	if (!this->getQuit())
	{
		srand(this->character->getSeed());
		int location = rand() % this->nrOfLocations;

		switch (location)
		{
		case EMPTY:
		{

			int randomnr = rand() % 2;
			this->locationString = "You are in an empty plane.";


			if (randomnr)
			{
				system("cls");
				std::cout << "ENEMY ENCOUTERED!" << "\n";
				system("pause");

				this->states->push(new CombatState(this->character, this->states));
			}
			break;
		}
		case FARM:
			this->locationString = "You are on a farm.";
			break;
		case CITY:
			this->locationString = "You are in a city.";
			break;
		case SHOP:
			this->locationString = "You find a shop.";
			break;
		case CHEST:
			this->locationString = "You found a chest!.";
			break;
		default:
			std::cout << "ERROR NO SUCH LOCATION!" << "\n";
			system("pause");
			break;
		}
	}
}

void TravelMenuState::updateMinimap()
{
	int startX = this->character->getX() - 2;
	if (startX < 0)
		startX = 0;

	int startY = this->character->getY() - 2;
	if (startY < 0)
		startY = 0;

	int endX = this->character->getX() + 2;
	int endY = this->character->getY() + 2;

	std::stringstream ss;

	for (size_t y = startY; y <= endY; y++)
	{
		for (size_t x = startX; x <= endX; x++)
		{
			srand(x + y);
			int location = rand() % this->nrOfLocations;

			if (x == this->character->getX() && y == this->character->getY())
				ss << "(P) ";
			else
			{
				switch (location)
				{
				case EMPTY:
					ss << "Em ";
					break;
				case FARM:
					ss << "Fa ";
					break;
				case CITY:
					ss << "Ci ";
					break;
				case SHOP:
					ss << "Sh ";
					break;
				case CHEST:
					ss << "Ch ";
					break;
				}
			}
		}

		ss << "\n";
	}

	this->minimapString = ss.str();
}

void TravelMenuState::updateMenu()
{
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;
	case 1:
		this->character->move(0, -1);
		break;
	case 2:
		this->character->move(0, 1);
		break;
	case 3:
		this->character->move(-1, 0);
		break;
	case 4:
		this->character->move(1, 0);
		break;
	case 5: //2018-11-28
		this->character->reset();
		this->character->addGold(-7);
		std::cout << "You drank potion and regained your strenght " << "\n";
		system("pause");
		break;
	default:
		system("CLS");
		std::cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

void TravelMenuState::update()
{
	this->updateMinimap();
	this->printMenu();
	this->updateMenu();
	this->updateEncounterMenu();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterCreatorState::CharacterCreatorState(
	std::vector<Character*>* characterList,
	unsigned& activeCharacter,
	std::stack<State*>* states)
	: State(), activeCharacter(activeCharacter), maxCharacters(5)
{
	this->characterList = characterList;
	this->states = states;
}

CharacterCreatorState::~CharacterCreatorState()
{

}

//Funkcijos
void CharacterCreatorState::createCharacter()
{
	if (this->characterList->size() < this->maxCharacters)
	{
		std::string name = "";
		std::string bio = "";

		std::cout << " Name: ";
		std::getline(std::cin, name);

		this->characterList->push_back(new Character(name));

		std::cout << " Character " << name << " created." << "\n" << "\n";
	}
	else
	{
		std::cout << " Max number of characters reached!" << "\n";
	}
}

void CharacterCreatorState::printMenu()
{
	system("CLS");
	std::cout << " --- Character Creator ---" << "\n" << "\n"
		<< " Characters: " << std::to_string(this->characterList->size()) << " / " << std::to_string(this->maxCharacters) << "\n" << "\n"
		<< " (-1) Back to menu" << "\n"
		<< " (1) New Character" << "\n" << "\n";
}

void CharacterCreatorState::updateMenu()
{
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;
	case 1:
		system("CLS");
		this->createCharacter();
		system("PAUSE");
		break;
	default:
		system("CLS");
		std::cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

void CharacterCreatorState::update()
{
	this->printMenu();
	this->updateMenu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterSelectorState::CharacterSelectorState(
	std::vector<Character*>* characterList,
	unsigned& activeCharacter,
	std::stack<State*>* states)
	: State(),
	characterList(characterList),
	activeCharacter(activeCharacter),
	states(states)
{

}

CharacterSelectorState::~CharacterSelectorState()
{

}

//Funkcijos
void CharacterSelectorState::printMenu()
{
	system("CLS");
	std::cout << " --- Character Selector ---" << "\n" << "\n";

	std::cout << " (-1) Back to menu" << "\n";

	if (!this->characterList->empty())
	{
		for (size_t i = 0; i < this->characterList->size(); i++)
		{
			std::cout << " (" << i << ") " << this->characterList->at(i)->getMenuBar() << "\n";
		}
		std::cout << "\n";
	}
}

void CharacterSelectorState::updateMenu()
{
	// Loading funkcija ideti
	if (!this->characterList->empty())
	{
		int choice = this->getChoice();

		if (choice < 0)
		{
			this->setQuit(true);
		}
		else if (choice >= 0 && choice < this->characterList->size())
		{
			this->activeCharacter = choice;
			this->setQuit(true);
			std::cout << " Character " << choice << " selected." << "\n" << "\n";
			system("pause");
		}
		else
		{
			std::cout << " Error: Choice out of bounds! " << "\n" << "\n";
			system("pause");
		}
	}
	else
	{
		this->setQuit(true);
		std::cout << " No characters created!" << "\n" << "\n";
		system("pause");
	}
}

void CharacterSelectorState::update()
{
	this->printMenu();
	this->updateMenu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShopMenuState::ShopMenuState(
	Character*& character,
	std::stack<State*>* states)
	: character(character), State()
{
	this->states = states;
	this->Shop_items.add(Item(STICK));
	this->Shop_items.add(Item(STONE));
	this->Shop_items.add(Item(KNIFE));
	this->Shop_items.add(Item(WOODEN_AXE));
	this->Shop_items.add(Item(STEEL_SWORD));
	this->Shop_items.add(Item(ELVEN_BOW));
	this->Shop_items.add(Item(EMERALD_SWORD));
	this->Shop_items.add(Item(DRAGONBONE_SWORD));
	this->Shop_items.add(Item(OBSIDIAN_SWORD));
	this->Shop_items.add(Item(LEATHER_ARMOR));
	this->Shop_items.add(Item(CHAIN_ARMOR));
	this->Shop_items.add(Item(IRON_ARMOR));
	this->Shop_items.add(Item(STEEL_ARMOR));
	this->Shop_items.add(Item(DRAGON_BONE_ARMOR));
	this->Shop_items.add(Item(OBSIDIAN_ARMOR));

}

ShopMenuState::~ShopMenuState()
{

}

void ShopMenuState::printMenu()
{
	system("CLS");
	std::cout << gui::msg_menutitle("Shop Menu");

	//std::cout
	//	<< "Welcome " <<this->character->getName(); darasyti 

	std::cout
		<< "\n"
		<< std::string(4, ' ') << "Your amount of gold:" << this->character->getGold()
		<< "\n";
		
	std::cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Back to menu")
		<< gui::msg_menuitem(1, "Buy items")
		<< gui::msg_menuitem(2, "Sell items");
	 //2018-11-28
}

void ShopMenuState::updateMenu()
{
	bool Leave_Shop = false;
	switch (this->getChoice())
	{
	case -1:
		this->setQuit(true);
		break;
	case 1:
		system("CLS");

		while (!Leave_Shop == true) {
			std::cout << "You picked up a right place to buy new gear ! " << "\n";
			std::cout
				<< "\n"
				<< std::string(4, ' ') << "Your amount of gold:" << this->character->getGold()
				<< "\n"
				<< gui::msg_menudivider(40, '-')
				<< std::string(4, ' ') << "Our available equipment number: " << this->Shop_items.size()  << "\n" << "\n";
			;
			std::cout << this->Shop_items.toString() << "\n";
			std::cout << "\nChoose number of wanted Item or write -1 to get back\n\n Your choice: ";
			std::cin >> this->Desired_item;
			if (Desired_item < this->Shop_items.size() && Desired_item >= 0)
			{
				if (this->character->getGold() >= Shop_items.at(Desired_item).getValue())
				{
					std::cout << "You bought: " << Shop_items.at(Desired_item).getName();
					// delete padaryti is Shop meniu
					this->character->addGold(Shop_items.at(Desired_item).getValue()*-1);
					this->character->getInventory().add(Shop_items.at(Desired_item));
					this->Shop_items.remove(Desired_item);
				}
				else {
					std::cout << "Sorry but you don't have enought of gold to buy: " << Shop_items.at(Desired_item).getName()
							  << "It's value: " << Shop_items.at(Desired_item).getValue();
				}
			}
			else if (Desired_item == -1)
			{
				Leave_Shop = true;
			}
			else std::cout << "Invalid input" << "\n";
			system("PAUSE");
			system ("cls");
			
		}
		break;
	case 2:
		system("CLS");
		std::cout << "Our shop accepts everything so show me your items ! " << "\n";
		system("PAUSE");
		break;
	default:
		system("CLS");
		std::cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

void ShopMenuState::update()
{
	//dadeti
	this->printMenu();
	this->updateMenu();
}
