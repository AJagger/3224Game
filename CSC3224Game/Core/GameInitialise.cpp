/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* Basic static class to initialise the various Game objects and systems.
*/

#include "stdafx.h"
#include "GameInitialise.h"
#include "../Frameworks/DataArray.h"
#include "../Frameworks/DataArray.cpp" //Temp fix to Visual Studio linker errors
#include "GameObject.h"
#include "GameState.h"
#include "GameScene.h"
#include "../Frameworks/Sound.h"
#include "../Frameworks/ResouceLoader.h"
#include "Box2D.h"
#include "Dynamics/b2World.h"
#include "Common/b2Math.h"
#include "../Frameworks/PhysicsResolver.h"
#include "../Frameworks/CustContactListener.h"

GameInitialise::GameInitialise()
{
}

GameInitialise::~GameInitialise()
{
}

//Create the DataArrays for storing game assets and assemble the GameLoop
GameLoop* GameInitialise::InitialiseGame()
{
	//Initialise WWise Audio
	if (InitSoundEngine()) {

		//Create the Game State. This initialises the renderer and GLEW
		GameState* gameState = new GameState();

		//Initialise DataArrays of textures & Meshes contained within the game
		DataArray<Mesh*> *gameMeshes = new DataArray<Mesh*>();
		DataArray<GLuint> *gameTextures = new DataArray<GLuint>();
		DataArray<CollisionMesh> *gameCollisionMeshes = new DataArray<CollisionMesh>();

		if(ResourceLoader::LoadMeshes(gameMeshes, "Game\\CSC3224Game\\Meshes") &&
			ResourceLoader::LoadTextures(gameTextures, "Game\\CSC3224Game\\Textures") &&
			ResourceLoader::LoadCollisionMeshes(gameCollisionMeshes, "Game\\CSC3224Game\\CollisionMeshes"))
		{
			//Initialise PhysicsEngine
			b2World *world = InitPhysicsEngine();

			//Initialise Game Scene & load test level
			GameScene* gameScene = new GameScene(gameMeshes, gameTextures, gameCollisionMeshes, world);
			gameScene->LoadLevel("Game\\CSC3224Game\\LevelData\\Level1.csv");

			GameLoop* gameLoop = new GameLoop(gameState, gameScene);
			return gameLoop;
		}

		//If initialiser has reached this point then an error has occured. Clean up created objects and then return null
		delete gameMeshes;
		delete gameTextures;
		delete gameState;
		gameMeshes = nullptr;
		gameTextures = nullptr;
		gameState = nullptr;

		Sound::TerminateSoundEngine();
	}
}

bool GameInitialise::InitSoundEngine()
{
	return Sound::InitSoundEngine();
}

b2World* GameInitialise::InitPhysicsEngine()
{
	
	//Create a new physics world in which collisions and movement are simulated. Set the gravity to 0,0 as this is a 2D top-down game.
	b2World *world = new b2World(b2Vec2(0.0f, 0.0f));
	world->SetAllowSleeping(false);							//Set Sleeping to false
	world->SetContactListener(new CustContactListener);
	return world;
}


