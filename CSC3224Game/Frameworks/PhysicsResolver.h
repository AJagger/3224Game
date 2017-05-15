/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class joins the physics engine Box2D to the rest of the engine. It allows for the creation and processing of game engine objects and data into
* objects and data used by the physics engine and vica versa.
*/

#pragma once
#include "Box2D.h"
#include "Dynamics/b2World.h"
#include "../Game/DemoCode/DemoGameObject.h"
#include "Common/b2Math.h"
#include "DataArray.h"

struct CollisionMesh
{
	b2Vec2 *points;
	int pointCount;
};

class PhysicsResolver
{
public:
	PhysicsResolver();
	~PhysicsResolver();

	static b2Body* CreatePhysicsObjectFromGameObject(b2World *world, DemoGameObject *gameObject, CollisionMesh *collisionMesh);
	static void RemovePhysicsObjectFromWorld(b2World *world, DemoGameObject *gameobject);
	static void SimulateActions(b2World *world, DataArray<DemoGameObject> *gameObjects);
};
