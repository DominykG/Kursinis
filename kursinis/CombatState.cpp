#include "CombatState.h"

CombatState::CombatState(
	Character*& character,
	std::stack<State*>* states)
	: character(character), State()

{
	this->states = states;
}

CombatState::~CombatState()
{

}

//funkcijos
void CombatState::beginCombat()
{
	Enemy enemy(this->character->getLevel());
	bool endCombat = false;

	int turn = rand() % 2;
	int round = 0;
	srand(time(NULL));

	while (!endCombat)
	{
		
		std::string atkStr = "Player";
		std::string defStr = "Enemy";
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
		std::cout << "-------------------------------------------------" << "\n";
		std::cout << " Attacker: " << atkStr << "\n";
		std::cout << " Defender: " << defStr << "\n";
		std::cout << " Round: " << ++round << "\n";
		std::cout << "-------------------------------------------------" << "\n";

		int damage = 0;
		//Pataikymas
		if (random > 0 && random <= hitPercent)
		{
			
			
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

			std::cout << atkStr << " HIT " << defStr << " FOR " << damage << "!" << "\n";
		}
		//Gynyba
		else
		{
			std::cout << atkStr << " MISSED " << defStr << "\n";
		}

		//Isvedimas informacijos apie Character ir enemy
		std::cout << "-------------------------------------------------" << "\n";
		std::cout << " Hit rating: " << hitRating << " Percent: " << hitPercent << "\n";
		std::cout << " Defence: " << defence << " Percent: " << defPercent << "\n";
		std::cout << " Player Damage: " << this->character->getDamageMin() << " - " << this->character->getDamageMax() << "\n";
		std::cout << " Enemy Damage: " << enemy.getDamageMin() << " - " << enemy.getDamageMax() << "\n";
		std::cout << " Player HP: " << this->character->getHP() << " / " << this->character->getHPMax() << "\n";
		std::cout << " Enemy HP: " << enemy.getHP() << " / " << enemy.getHPMax() << "\n";
		std::cout << "-------------------------------------------------" << "\n";

		//Character pralose
		if (this->character->isDead())
		{
			endCombat = true;
			std::cout << "YOU ARE DEAD AND LOST SOME EXP AND GOLD!" << "\n";
			this->setQuit(true);
		}
		//Character laimejo
		else if (enemy.isDead())
		{
			endCombat = true;
			int gainedExp = rand() % (enemy.getLevel() * 20) + (enemy.getLevel() * 10);
			int gainedGold = rand() % (enemy.getLevel() * 10) + (enemy.getLevel() * 5);
			//Turetu dar ir daiktu drop'a gaut bet dar to nera
			this->character->addExp(gainedExp);
			this->character->addGold(gainedGold);
			std::cout << "YOU DEFEATED THE ENEMY AND GAINED " << gainedExp << " EXP and " << gainedGold << " gold " <<"\n";
			
			this->setQuit(true);
			
		}
		
		//If kuris keicia ejimus
		turn = turn ? false : true;

		system("pause");
	}
}

void CombatState::printMenu()
{
	system("CLS");
	std::cout << " --- Combat Menu ---" << "\n" << "\n";
	std::cout << this->character->getMenuBar() << "\n" << "\n";
	std::cout << " (1) Begin Combat" << "\n"
		<< " (2) Flee" << "\n"
		//<< " (3) Heal" << "\n"
		<< "\n";
}

void CombatState::updateMenu()
{
	switch (this->getChoice())
	{
	case 1:
		this->beginCombat();
		std::cout << "END OF COMBAT." << "\n";
		system("pause");
		break;

	case 2:
		system("cls");
		std::cout << "You fled and lost some valuables..." << "\n";
		std::cout << this->character->flee() << "\n";
		system("pause");
		this->setQuit(true);
		break;

	/*case 3: //2018-11-28
		system("cls");
		this->character->reset();
		std::cout << "(TESTING) You have rested..." << "\n";
		system("pause");
		break;*/

	default:
		system("CLS");
		std::cout << "Not a valid option! " << "\n";
		system("PAUSE");
		break;
	}
}

//Funkcijos


void CombatState::update()
{
	this->printMenu();
	this->updateMenu();
}
