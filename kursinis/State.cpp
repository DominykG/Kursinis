#include "State.h"

State::State()
{
	this->quit = false;
}

State::~State()
{

}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::setQuit(const bool quit)
{
	this->quit = quit;
}

int State::getChoice() const
{
	int choice = 0;

	std::cout << std::string(4, ' ') << " | - [[ Enter choice: ";
	std::cin >> std::setw(1) >> choice;

	while (!std::cin.good())
	{
		std::cout << " ERROR: Faulty Input!" << "\n";

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::string(4, ' ') << " | - [[ Enter choice: ";
		std::cin >> std::setw(1) >> choice;
	}

	std::cout << "\n";

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	return choice;
}
