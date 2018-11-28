#include "OtherStates.h"
#include "MenuStates.h"


GameState::GameState(
	Character*& character,
	stack<State*>*states)
	: State(), character(character)
{
	this->states = states;
}

GameState::~GameState()
{

}

//Functions
void GameState::printMenu() const
{
	system("CLS");
	cout << gui::msg_menutitle("Game Menu");

	cout << this->character->getMenuBar();

	cout
		<< gui::msg_menudivider(40, '-')
		<< gui::msg_menuitem(-1, "Quit to main menu.")
		<< gui::msg_menuitem(1, "Character Menu.")
		<< gui::msg_menuitem(2, "Shop Menu.")
		<< gui::msg_menuitem(3, "Travel Menu.")
		<< gui::msg_menuitem(4, "Rest Menu.")
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

		break;

	case 3:
		this->states->push(new TravelMenuState(this->character, this->states));
		break;

	case 4:
		system("cls");
		this->character->reset();
		cout << "You have rested..." << "\n";
		system("pause");
		break;

	default:
		system("CLS");
		cout << "Not a valid option!" << "\n";
		system("PAUSE");
		break;
	}
}

void GameState::update()
{
	//Print the menu
	this->printMenu();

	//Get a choice and choose valid option
	this->updateMenu();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterCreatorState::CharacterCreatorState(
	vector<Character*>* characterList,
	unsigned& activeCharacter,
	stack<State*>* states)
	: State(), activeCharacter(activeCharacter), maxCharacters(5)
{
	this->characterList = characterList;
	this->states = states;
}

CharacterCreatorState::~CharacterCreatorState()
{

}

//Functions
void CharacterCreatorState::createCharacter()
{
	if (this->characterList->size() < this->maxCharacters)
	{
		string name = "";
		string bio = "";

		cout << " Name: ";
		getline(cin, name);

		cout << " Biography: ";
		getline(cin, bio);

		this->characterList->push_back(new Character(name, bio));

		cout << " Character " << name << " created." << "\n" << "\n";
	}
	else
	{
		cout << " Max number of characters reached!" << "\n";
	}
}

void CharacterCreatorState::printMenu()
{
	system("CLS");
	cout << " --- Character Creator ---" << "\n" << "\n"
		<< " Characters: " << to_string(this->characterList->size()) << " / " << to_string(this->maxCharacters) << "\n" << "\n"
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
		cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

void CharacterCreatorState::update()
{
	this->printMenu();
	this->updateMenu();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CharacterSelectorState::CharacterSelectorState(
	vector<Character*>* characterList,
	unsigned& activeCharacter,
	stack<State*>* states)
	: State(),
	characterList(characterList),
	activeCharacter(activeCharacter),
	states(states)
{

}

CharacterSelectorState::~CharacterSelectorState()
{

}

//Functions
void CharacterSelectorState::printMenu()
{
	system("CLS");
	cout << " --- Character Selector ---" << "\n" << "\n";

	cout << " (-1) Back to menu" << "\n";

	if (!this->characterList->empty())
	{
		for (size_t i = 0; i < this->characterList->size(); i++)
		{
			cout << " (" << i << ") " << this->characterList->at(i)->getMenuBar() << "\n";
		}
		cout << "\n";
	}
}

void CharacterSelectorState::updateMenu()
{
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
			cout << " Character " << choice << " selected." << "\n" << "\n";
			system("pause");
		}
		else
		{
			cout << " Error: Choice out of bounds! " << "\n" << "\n";
			system("pause");
		}
	}
	else
	{
		this->setQuit(true);
		cout << " No characters created!" << "\n" << "\n";
		system("pause");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CombatState::CombatState(
	Character*& character,
	stack<State*>* states)
	: character(character), State()

{
	this->states = states;
}

CombatState::~CombatState()
{

}

//functions
void CombatState::beginCombat()
{
	Enemy enemy(this->character->getLevel());
	bool endCombat = false;

	int turn = rand() % 2;
	int round = 0;

	srand(time(NULL));

	while (!endCombat)
	{
		//Test for player attacking and enemy defending
		string atkStr = "Player";
		string defStr = "Enemy";
		float hitRating = static_cast<float>(this->character->getHitRating());
		float defence = static_cast<float>(enemy.getDefence());

		if (!turn)
		{
			atkStr = "Enemy";
			defStr = "Player";
			hitRating = static_cast<float>(enemy.getHitRating());
			defence = static_cast<float>(this->character->getDefence());
		}

		float totalHitDef = hitRating + defence;
		float hitPercent = 100.f * (hitRating / totalHitDef);
		float defPercent = 100.f * (defence / totalHitDef);

		int random = rand() % 100 + 1;

		system("cls");
		cout << "-------------------------------------------------" << "\n";
		cout << " Attacker: " << atkStr << "\n";
		cout << " Defender: " << defStr << "\n";
		cout << " Round: " << ++round << "\n";
		cout << "-------------------------------------------------" << "\n";

		//Hit
		if (random > 0 && random <= hitPercent)
		{
			int damage = 0;

			if (turn)
			{
				damage = rand() % (this->character->getDamageMax() - this->character->getDamageMin()) + this->character->getDamageMin();
				enemy.takeDamage(damage);
			}
			else
			{
				damage = rand() % (enemy.getDamageMax() - enemy.getDamageMin()) + enemy.getDamageMin();
				this->character->takeDamage(damage);
			}

			cout << atkStr << " HIT " << defStr << " FOR " << damage << "!" << "\n";
		}
		//Defend
		else
		{
			cout << atkStr << " MISSED " << defStr << "\n";
		}

		//Data
		cout << "-------------------------------------------------" << "\n";
		cout << " Hit rating: " << hitRating << " Percent: " << hitPercent << "\n";
		cout << " Defence: " << defence << " Percent: " << defPercent << "\n";
		cout << " Player Damage: " << this->character->getDamageMin() << " - " << this->character->getDamageMax() << "\n";
		cout << " Enemy Damage: " << enemy.getDamageMin() << " - " << enemy.getDamageMax() << "\n";
		cout << " Player HP: " << this->character->getHP() << " / " << this->character->getHPMax() << "\n";
		cout << " Enemy HP: " << enemy.getHP() << " / " << enemy.getHPMax() << "\n";
		cout << "-------------------------------------------------" << "\n";

		//Loss
		if (this->character->isDead())
		{
			endCombat = true;
			cout << "YOU ARE DEAD AND YOU LOST SOME EXP AND GOLD!" << "\n";
			this->setQuit(true);
		}
		//Win
		else if (enemy.isDead())
		{
			endCombat = true;
			int gainedExp = rand() % (enemy.getLevel() * 20) + (enemy.getLevel() * 10);
			this->character->addExp(gainedExp);
			cout << "YOU DEFEATED THE ENEMY AND GAINED " << gainedExp << " EXP!" << "\n";
			this->setQuit(true);
		}

		//Switch turn
		turn = turn ? false : true;

		system("pause");
	}
}

void CombatState::printMenu()
{
	system("CLS");
	cout << " --- Combat Menu ---" << "\n" << "\n";
	cout << this->character->getMenuBar() << "\n" << "\n";
	cout << " (1) Begin Combat" << "\n"
		<< " (2) Flee" << "\n"
		<< " (3) Heal" << "\n"
		<< "\n";
}

void CombatState::updateMenu()
{
	switch (this->getChoice())
	{
	case 1:
		this->beginCombat();
		cout << "END OF COMBAT." << "\n";
		system("pause");
		//this->setQuit(true);
		break;

	case 2:
		system("cls");
		cout << "You fled and lost some valuables..." << "\n";
		cout << this->character->flee() << "\n";
		system("pause");
		this->setQuit(true);
		break;

	case 3:
		system("cls");
		this->character->reset();
		cout << "(TESTING) You have rested..." << "\n";
		system("pause");
		break;

	default:
		system("CLS");
		cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

//Functions


void CombatState::update()
{
	this->printMenu();
	this->updateMenu();
}
