/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class contains all of the logic for the game and is called from multiple locations. It also contains very basic AI methods to instruct the enemies where to move and where to shoot.
*/

#include "stdafx.h"
#include "GameRules.h"
#include "../../Frameworks/DataArray.cpp"
#include <valarray>
#include "../../Frameworks/Draw.h"

GameRules::GameRules()
{
}

GameRules::~GameRules()
{
}

void GameRules::EnactGameRules(GameScene * gameScene, GameState * gameState)
{
	//For the demo project the only game specific rule to be checked and acted upon is whether the victory conditions have been met
	if (CheckVictoryConditions(gameScene, gameState))
	{
		gameState->end = true;
	}
	DeleteOOBProjectiles(gameScene, gameState);
	CheckForEntitiesToRemove(gameScene);
	UpdateHUD(gameScene, gameState);
}

void GameRules::Fire(GameScene * gameScene, GameState * gameState, StandardGameObject * source, Vector2 targetLocation)
{
	int ticksSinceLastShot = gameState->tickCount - source->wep1LastFire;

	if (source->weapon == BC304_RAILGUN)
	{
		//Check time since last firing
		if (ticksSinceLastShot >= FIRERATE_BC304_RAILGUN)
		{

			source->wep1LastFire = gameState->tickCount;

			//Set the spawn points on the Deadalus model
			Vector3 spawn1InitialPosition = Vector3(-0.3, 0.6, 0);
			Vector3 spawn2InitialPosition = Vector3(0.3, 0.6, 0);

			//Update these for the rotation and position of the model
			double rotationRadians = source->rotation * (PI / 180.0f);

			Vector3 spawn1Position =
				Vector3(spawn1InitialPosition.x*cos(rotationRadians) - spawn1InitialPosition.y*sin(rotationRadians),
					spawn1InitialPosition.y*cos(rotationRadians) + spawn1InitialPosition.x*sin(rotationRadians), 0);
			Vector3 spawn2Position =
				Vector3(spawn2InitialPosition.x*cos(rotationRadians) - spawn2InitialPosition.y*sin(rotationRadians),
					spawn2InitialPosition.y*cos(rotationRadians) + spawn2InitialPosition.x*sin(rotationRadians), 0);
			spawn1Position = spawn1Position + source->position;
			spawn2Position = spawn2Position + source->position;

			//Spawn projectile at position 1
			StandardGameObject *newProjectile = gameScene->gameObjects.CreateNew();
			newProjectile->ConfigureDefaultProjectile(5, 6);
			newProjectile->physMeshId = 3;
			newProjectile->hasTarget = false;
			newProjectile->weapon = BC304_RAILGUN;
			newProjectile->AIEnabled = false;
			newProjectile->hostile = false;
			newProjectile->markedForDeletion = false;

			Vector2 movement = targetLocation - Vector2(spawn1Position.x, spawn1Position.y);
			movement.Normalise();
			movement = movement * 0.01f;

			newProjectile->movementVector = movement;
			newProjectile->position = spawn1Position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));


			//Spawn projectile at position 2
			newProjectile = gameScene->gameObjects.CreateNew();
			newProjectile->ConfigureDefaultProjectile(5, 6);
			newProjectile->physMeshId = 3;
			newProjectile->hasTarget = false;
			newProjectile->weapon = BC304_RAILGUN;
			newProjectile->AIEnabled = false;
			newProjectile->hostile = false;
			newProjectile->markedForDeletion = false;

			movement = targetLocation - Vector2(spawn2Position.x, spawn2Position.y);
			movement.Normalise();
			movement = movement * 0.01f;

			newProjectile->movementVector = movement;
			newProjectile->position = spawn2Position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));
		}
	}

	if (source->weapon == HATAK_CANNON)
	{
		//Check time since last firing
		if (ticksSinceLastShot >= FIRERATE_HATAK_CANNON)
		{
			source->wep1LastFire = gameState->tickCount;

			//Spawn projectile at position 1
			StandardGameObject *newProjectile = gameScene->gameObjects.CreateNew();
			newProjectile->ConfigureDefaultProjectile(9, 6);
			newProjectile->physMeshId = 7;
			newProjectile->hasTarget = false;
			newProjectile->weapon = HATAK_CANNON;
			newProjectile->AIEnabled = false;
			newProjectile->hostile = true;
			newProjectile->markedForDeletion = false;

			Vector2 movement = targetLocation - Vector2(source->position.x, source->position.y);
			movement.Normalise();
			movement = movement * 0.005f;

			newProjectile->movementVector = movement;
			newProjectile->position = source->position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));
		}
	}

	if (source->weapon == GLIDER_CANNON)
	{
		//Check time since last firing
		if (ticksSinceLastShot >= FIRERATE_GLIDER_CANNON)
		{

			source->wep1LastFire = gameState->tickCount;

			//Set the spawn points on the Glider model
			Vector3 spawn1InitialPosition = Vector3(-0.2, -0.1, 0);
			Vector3 spawn2InitialPosition = Vector3(0.2, -0.1, 0);

			//Update these for the rotation and position of the model
			double rotationRadians = source->rotation * (PI / 180.0f);

			Vector3 spawn1Position =
				Vector3(spawn1InitialPosition.x*cos(rotationRadians) - spawn1InitialPosition.y*sin(rotationRadians),
					spawn1InitialPosition.y*cos(rotationRadians) + spawn1InitialPosition.x*sin(rotationRadians), 0);
			Vector3 spawn2Position =
				Vector3(spawn2InitialPosition.x*cos(rotationRadians) - spawn2InitialPosition.y*sin(rotationRadians),
					spawn2InitialPosition.y*cos(rotationRadians) + spawn2InitialPosition.x*sin(rotationRadians), 0);
			spawn1Position = spawn1Position + source->position;
			spawn2Position = spawn2Position + source->position;

			//Spawn projectile at position 1
			StandardGameObject *newProjectile = gameScene->gameObjects.CreateNew();
			newProjectile->ConfigureDefaultProjectile(8, 6);
			newProjectile->physMeshId = 6;
			newProjectile->hasTarget = false;
			newProjectile->weapon = GLIDER_CANNON;
			newProjectile->AIEnabled = false;
			newProjectile->hostile = true;
			newProjectile->markedForDeletion = false;

			Vector2 movement = targetLocation - Vector2(spawn1Position.x, spawn1Position.y);
			movement.Normalise();
			movement = movement * 0.01f;

			newProjectile->movementVector = movement;
			newProjectile->position = spawn1Position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));
			
			//Spawn projectile at position 2
			newProjectile = gameScene->gameObjects.CreateNew();
			newProjectile->ConfigureDefaultProjectile(8, 6);
			newProjectile->physMeshId = 6;
			newProjectile->hasTarget = false;
			newProjectile->weapon = GLIDER_CANNON;
			newProjectile->AIEnabled = false;
			newProjectile->hostile = true;
			newProjectile->markedForDeletion = false;

			movement = targetLocation - Vector2(spawn2Position.x, spawn2Position.y);
			movement.Normalise();
			movement = movement * 0.01f;

			newProjectile->movementVector = movement;
			newProjectile->position = spawn2Position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));
		}
	}
}

void GameRules::AIOperations(GameScene * gameScene, GameState * gameState)
{
	//Search through scene entities looking for player controlled entities.
	bool playerFound = false;
	StandardGameObject *playerEntity = gameScene->gameObjects.TryToGetFirst();

	if (playerEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (playerEntity->playerControlled)
		{
			playerFound = true;
		}

		while (gameScene->gameObjects.IsNext() && !playerFound)
		{
			playerEntity = gameScene->gameObjects.Next();
			if (playerEntity->playerControlled)
			{
				playerFound = true;
			}
		}
	}

	//Loop through entities and perform AI operations on AI entities IF player object has been found
	if(playerFound)
	{
		StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
		if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
		{
			if (returnedEntity->AIEnabled)
			{
				AIMove(gameScene, returnedEntity, playerEntity);
				AITarget(gameScene, gameState, returnedEntity, playerEntity);
			}

			while (gameScene->gameObjects.IsNext())
			{
				returnedEntity = gameScene->gameObjects.Next();
				if (returnedEntity->AIEnabled)
				{
					AIMove(gameScene, returnedEntity, playerEntity);
					AITarget(gameScene, gameState, returnedEntity, playerEntity);
				}
			}
		}
	}


}

void GameRules::Damage(StandardGameObject * source, StandardGameObject * target)
{
	if(target->entityType == PLAYER || target->entityType == NPC)
	{
		int damage = 0;

		switch(source->weapon)
		{
			case BC304_RAILGUN: damage = DAMAGE_BC304_RAILGUN; break;
			case HATAK_CANNON: damage = DAMAGE_HATAK_CANNON; break;
			case GLIDER_CANNON: damage = DAMAGE_GLIDER_CANNON; break;
		}

		target->health = target->health - damage;
	}
}

void GameRules::UpdateCamera(GameScene *gameScene, GameState *gameState)
{
	bool playerFound = false;

	//Search through scene entities looking for the player ship
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->playerControlled && returnedEntity->entityType == PLAYER)
		{
			playerFound = true;
		}

		while (gameScene->gameObjects.IsNext() && !playerFound)
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->playerControlled && returnedEntity->entityType == PLAYER)
			{
				playerFound = true;
			}
		}
	}

	//If player found, update the camera
	if(playerFound)
	{
		Draw::UpdateCamera(gameState, returnedEntity->position);
	}

}

bool GameRules::CheckVictoryConditions(GameScene * gameScene, GameState * gameState)
{
	int playerCount = 0;
	int NPCCount = 0;

	bool victory = false;

	//Search through scene entities looking for player controlled entities. Once found, check if their position to see if they have completed the level
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->entityType == PLAYER)
		{
			playerCount++;
		}
		else if (returnedEntity->entityType == NPC)
		{
			NPCCount++;
		}

		while (gameScene->gameObjects.IsNext())
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->entityType == PLAYER)
			{
				playerCount++;
			}
			else if (returnedEntity->entityType == NPC)
			{
				NPCCount++;
			}
		}
	}

	if(playerCount == 0 || NPCCount == 0)
	{
		victory = true;
	}

	return victory;
}

void GameRules::CheckForEntitiesToRemove(GameScene * gameScene)
{
	//Search through scene entities looking to see if entities need to be removed
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->markedForDeletion || returnedEntity->health <= 0)
		{
			int entityId = gameScene->gameObjects.GetId(*returnedEntity);
			gameScene->DeleteRelatedPhysicsObject(entityId);
			gameScene->gameObjects.Free(entityId);
		}

		while (gameScene->gameObjects.IsNext())
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->markedForDeletion || returnedEntity->health <= 0)
			{
				int entityId = gameScene->gameObjects.GetId(*returnedEntity);
				gameScene->DeleteRelatedPhysicsObject(entityId);
				gameScene->gameObjects.Free(entityId);
			}
		}
	}

}

//Check for projectiles that are too far from the current section of the map and delete
void GameRules::DeleteOOBProjectiles(GameScene * gameScene, GameState * gameState)
{
	//Search through scene entities looking to see if entities need to be removed
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->entityType == PROJECTILE)
		{
			if(returnedEntity-> position. x > 36 || returnedEntity->position.x < -1 || returnedEntity->position.y > (30 + gameState->cameraYValue) || returnedEntity->position.y < (-10 + gameState->cameraYValue))
			{
				returnedEntity->markedForDeletion = true;
			}
		}

		while (gameScene->gameObjects.IsNext())
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->entityType == PROJECTILE)
			{
				if (returnedEntity->position.x > 36 || returnedEntity->position.x < -1 || returnedEntity->position.y >(30 + gameState->cameraYValue) || returnedEntity->position.y < (-10 + gameState->cameraYValue))
				{
					returnedEntity->markedForDeletion = true;
				}
			}
		}
	}

}

void GameRules::AIMove(GameScene * gameScene, StandardGameObject * aIObject, StandardGameObject * playerObject)
{
	//Check distance between the NPC and Player. If within distance and not too close, move towards player
	float distance = (aIObject->position - playerObject->position).Length();
	if (distance < 0)
	{
		distance = distance * -1;
	}

	if (distance < 20 && distance > 4)
	{
		if (aIObject->shipType == SHIP_GLIDER)
		{
			Vector3 movementVector = (playerObject->position - aIObject->position);
			movementVector.z = 0;
			movementVector.Normalise();
			aIObject->movementVector = Vector2(movementVector.x * 0.001, movementVector.y * 0.001);
		}
	}
}

void GameRules::AITarget(GameScene * gameScene, GameState *gameState, StandardGameObject * aIObject, StandardGameObject * playerObject)
{
	//Check distance between the NPC and Player. If within distance, fire upon the player
	float distance = (aIObject->position - playerObject->position).Length();
	if (distance < 0)
	{
		distance = distance * -1;
	}

	if(distance < 20)
	{
		Fire(gameScene, gameState, aIObject, Vector2(playerObject->position.x, playerObject->position.y));
	}
}

void GameRules::UpdateHUD(GameScene * gameScene, GameState * gameState)
{
	bool playerFound = false;

	//Search through scene for player entity
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->entityType == PLAYER && returnedEntity->playerControlled)
		{
			gameState->HUDHealth = (float)(returnedEntity->health) / 5000; //SHIP_BC304 health %
			playerFound = true;
		}

		while (gameScene->gameObjects.IsNext() && !playerFound)
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->entityType == PLAYER && returnedEntity->playerControlled)
			{
				gameState->HUDHealth = (float)(returnedEntity->health) / 5000; //SHIP_BC304 health %
				playerFound = true;
			}
		}
	}

}

