// CSC3224Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Core/GameShutdown.h"
#include "Core/GameInitialise.h"


int main()
{
	bool finish = false;

	GameLoop *game = GameInitialise::InitialiseGame();

	while (!finish) {
		if (game)
		{
			game->RunLoop();
		}
		else
		{
			//Something ****ed up
		}
		cout << "GameLoop Ended";

		game->ResetLevel();
	}

	if (game)
	{
		GameShutdown::TerminateGame(game);
	}

    return 0;
}

