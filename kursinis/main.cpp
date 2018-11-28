#include"Game.h"



int main()
{
	Game game;

	//Zaidimo ciklas
	while (!game.getQuit())
	{
		game.update();
	}

	system("PAUSE");

	return 0; 
}