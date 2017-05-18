// CSC3224Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Core/GameShutdown.h"
#include "Core/GameInitialise.h"


int main()
{
	bool finish = false;

	while (!finish) {
		GameLoop *game = GameInitialise::InitialiseGame();
		if (game)
		{
			game->RunLoop();
			GameShutdown::TerminateGame(game);
		}
		else
		{
			//Something ****ed up
		}
		finish = true;
		cout << "GameLoop Ended";
	}

    return 0;
}

