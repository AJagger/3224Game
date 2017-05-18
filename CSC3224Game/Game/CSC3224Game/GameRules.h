/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* A very basic implementation of a class dealing with game-specific logic. For an actual game, the victory conditions would be a lot more complex but for the demo
* the simple victory condition implemented is enough.
* This class is called in the game loop and is intended to contain game logic in addition to the victory conditions in the game for coursework 2.
*/

#pragma once
#include "../../Core/GameScene.h"
#include "../../Core/GameState.h"

class GameRules
{
public:
	GameRules();
	~GameRules();

	static void EnactGameRules(GameScene *gameScene, GameState *gameState);
	static void Fire(GameScene *gameScene, StandardGameObject* source, Vector2 mouseLocation);

private:
	static bool CheckVictoryConditions(GameScene *gameScene, GameState *gameState);
	static void CheckForEntitiesToRemove(GameScene * gameScene);
};
