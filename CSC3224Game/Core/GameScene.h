/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class stores all the information about the (non-physics) game world. It has DataArrays containing all game assets (meshes, textures, collision meshes)
* and contains the physics world in which the physics simulations are performed. It contains a few functions but is mostly used to pass to other engine functions
* and provide them with the level and game data needed.
*/

#pragma once
#include "GameObject.h"
#include "../Frameworks/DataArray.h"
#include "../Game/DemoCode/DemoGameObject.h"
#include "../Renderer/nclgl/Mesh.h"
#include "../Physics/Box2D-master/Box2D/Box2D/Dynamics/b2World.h"
#include "Box2D.h"
#include "Box2D/Common/b2Math.h"
#include "../Frameworks/PhysicsResolver.h"

class GameScene
{
public:
	GameScene(DataArray<Mesh*> *gameMeshes, DataArray<GLuint> *gameTextures, DataArray<CollisionMesh> *gameCollisionMeshes, b2World *world);
	~GameScene();

	void CreateRelatedPhysicsObject(int gameObjectId);
	void DeleteRelatedPhysicsObject(int gameObjectId);

	DataArray<DemoGameObject> gameObjects = DataArray<DemoGameObject>();
	DataArray<Mesh*> *gameMeshes;
	DataArray<GLuint> *gameTextures;
	DataArray<CollisionMesh> *gameCollisionMeshes;
	b2World *world;

	void LoadLevel(const string &sceneFile);
	void LoadTestLevel();

};
