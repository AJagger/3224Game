/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class contains all of the logic for the game and is called from multiple locations. It also contains very basic AI methods to instruct the enemies where to move and where to shoot.
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
	static void Fire(GameScene *gameScene, GameState * gameState, StandardGameObject* source, Vector2 targetLocation);
	static void AIOperations(GameScene *gameScene, GameState *gameState);
	static void Damage(StandardGameObject* source, StandardGameObject* target);
	static void UpdateCamera(GameScene *gameScene, GameState *gameState);

	const static int FIRERATE_BC304_RAILGUN = 15;
	const static int FIRERATE_HATAK_CANNON = 35;
	const static int FIRERATE_GLIDER_CANNON = 20; //480
	const static int DAMAGE_BC304_RAILGUN = 150;
	const static int DAMAGE_HATAK_CANNON = 300;
	const static int DAMAGE_GLIDER_CANNON = 25;

private:

	static bool CheckVictoryConditions(GameScene *gameScene, GameState *gameState);
	static void CheckForEntitiesToRemove(GameScene * gameScene);
	static void DeleteOOBProjectiles(GameScene * gameScene, GameState * gameState);
	static void AIMove(GameScene *gameScene, StandardGameObject* aIObject, StandardGameObject* playerObject);
	static void AITarget(GameScene *gameScene, GameState *gameState, StandardGameObject* aIObject, StandardGameObject* playerObject);
	static void UpdateHUD(GameScene *gameScene, GameState *gameState);

};
