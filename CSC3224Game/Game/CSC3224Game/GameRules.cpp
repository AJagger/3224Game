#include "stdafx.h"
#include "GameRules.h"
#include "../../Frameworks/DataArray.cpp"
#include <valarray>

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
	CheckForEntitiesToRemove(gameScene);
}

void GameRules::Fire(GameScene * gameScene, StandardGameObject * source, Vector2 mouseLocation)
{
	//Check time since last firing
	if((clock() - source->wep1LastFire) >= 240)
	{
		source->wep1LastFire = clock();

		if (source->weapon == BC304_RAILGUN)
		{
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

			Vector2 movement = mouseLocation - Vector2(spawn1Position.x, spawn1Position.y);
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

			movement = mouseLocation - Vector2(spawn2Position.x, spawn2Position.y);
			movement.Normalise();
			movement = movement * 0.01f;

			newProjectile->movementVector = movement;
			newProjectile->position = spawn2Position;
			newProjectile->position.z = 2;

			gameScene->CreateRelatedPhysicsObject(gameScene->gameObjects.GetId(*newProjectile));
			//StandardGameObject *newProjectile = gameScene->gameObjects.CreateNew();
			//newProjectile->ConfigureDefaultProjectile(5, 6);
			//newProjectile->physMeshId = 3;
			//newProjectile->hasTarget = false;
			//newProjectile->weapon = BC304_RAILGUN;
			//newProjectile->AIEnabled = false;
			//newProjectile->hostile = false;
			//newProjectile->markedForDeletion = false;

			//newProjectile->position = Vector3(mouseLocation.x, mouseLocation.y, 1);
		}
	}
}

bool GameRules::CheckVictoryConditions(GameScene * gameScene, GameState * gameState)
{
	//Victory Conditions listed below:
	Vector3 victoryPosition = Vector3(24, 12, 0);


	bool victory = false;

	//Search through scene entities looking for player controlled entities. Once found, check if their position to see if they have completed the level
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->playerControlled)
		{
			if (returnedEntity->position.x >= victoryPosition.x && returnedEntity->position.y >= victoryPosition.y)
			{
				victory = true; //Player craft has reached the end of the demo maze!
			}
		}

		while (gameScene->gameObjects.IsNext())
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->playerControlled)
			{
				if (returnedEntity->position.x >= victoryPosition.x && returnedEntity->position.y >= victoryPosition.y)
				{
					victory = true; //Player craft has reached the end of the demo maze!
				}
			}
		}
	}

	return victory;
}

void GameRules::CheckForEntitiesToRemove(GameScene * gameScene)
{
	//Search through scene entities looking to see if entities need to be removed
	StandardGameObject *returnedEntity = gameScene->gameObjects.TryToGetFirst();
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (returnedEntity->markedForDeletion)
		{
			int entityId = gameScene->gameObjects.GetId(*returnedEntity);
			gameScene->DeleteRelatedPhysicsObject(entityId);
			gameScene->gameObjects.Free(entityId);
		}

		while (gameScene->gameObjects.IsNext())
		{
			returnedEntity = gameScene->gameObjects.Next();
			if (returnedEntity->markedForDeletion)
			{
				int entityId = gameScene->gameObjects.GetId(*returnedEntity);
				gameScene->DeleteRelatedPhysicsObject(entityId);
				gameScene->gameObjects.Free(entityId);
			}
		}
	}

}
