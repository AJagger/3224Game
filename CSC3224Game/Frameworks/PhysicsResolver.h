/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class joins the physics engine Box2D to the rest of the engine. It allows for the creation and processing of game engine objects and data into
* objects and data used by the physics engine and vica versa.
*/

#pragma once
#include "../Physics/Box2D-master/Box2D/Box2D/Box2D.h"
#include "../Physics/Box2D-master/Box2D/Box2D/Dynamics/b2World.h"
#include "../Game/DemoCode/DemoGameObject.h"
#include "../Physics/Box2D-master/Box2D/Box2D/Common/b2Math.h"
#include "DataArray.h"
#include "../Game/CSC3224Game/StandardGameObject.h"

enum CollisionMeshType
{
	CM_POLYGON = 0,
	CM_CIRCLE = 1
};

struct CollisionMesh
{
	CollisionMeshType meshType;
	b2Vec2 *points;
	int pointCount;
	float radius;
};

class PhysicsResolver
{
public:
	PhysicsResolver();
	~PhysicsResolver();

	static b2Body* CreatePhysicsObjectFromGameObject(b2World *world, StandardGameObject *gameObject, CollisionMesh *collisionMesh);
	static void RemovePhysicsObjectFromWorld(b2World *world, StandardGameObject *gameobject);
	static void SimulateActions(b2World *world, DataArray<StandardGameObject> *gameObjects);
};
