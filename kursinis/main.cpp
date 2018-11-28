#include"Game.h"

//Github kommentaras

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