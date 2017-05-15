/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class joins the physics engine Box2D to the rest of the engine. It allows for the creation and processing of game engine objects and data into
* objects and data used by the physics engine and vica versa.
*/

#include "stdafx.h"
#include "PhysicsResolver.h"
#include "Box2D.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Common/b2Math.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include <memory>
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Collision/Shapes/b2Shape.h"

PhysicsResolver::PhysicsResolver()
{
}


PhysicsResolver::~PhysicsResolver()
{
}

b2Body * PhysicsResolver::CreatePhysicsObjectFromGameObject(b2World *world, DemoGameObject * gameObject, CollisionMesh *collisionMesh)
{
	//Create the body definition which contains the physics object attributes
	b2BodyDef physObjectDefinition = b2BodyDef();
	gameObject->staticObject ? physObjectDefinition.type = b2_staticBody : physObjectDefinition.type = b2_dynamicBody;
	physObjectDefinition.position.Set(gameObject->position.x, gameObject->position.y);
	physObjectDefinition.userData = gameObject;

	//Set up the actual collision box shape
	b2PolygonShape physShape;
	physShape.Set(collisionMesh->points, collisionMesh->pointCount);

	//More attribute setting and inclusion of the collision box shape
	b2FixtureDef physShapeDef;
	physShapeDef.shape = &physShape;
	physShapeDef.density = 10.0;
	physShapeDef.isSensor = false;

	//Use the above definitions to create the physics object
	b2Body *objectBody = world->CreateBody(&physObjectDefinition);
	objectBody->CreateFixture(&physShapeDef);

	return objectBody;
}

void PhysicsResolver::RemovePhysicsObjectFromWorld(b2World * world, DemoGameObject * gameobject)
{
	b2Body *deleteBody = NULL;

	for(b2Body *b = world->GetBodyList(); b; b= b->GetNext())
	{
		if(b->GetUserData() != NULL)
		{
			if(gameobject == b->GetUserData())
			{
				deleteBody = b;
			}
		}
	}

	if(deleteBody != NULL)
	{
		world->DestroyBody(deleteBody);
	}

}

//Update the physics objects using game engine data, run the simulation for a tick and then update the game engine objects with physics engine data.
void PhysicsResolver::SimulateActions(b2World *world, DataArray<DemoGameObject> *gameObjects)
{
	//Iterate through the game objects and if they are non-static, update their movement vectors within the simulation
	DemoGameObject *returnedEntity = gameObjects->TryToGetFirst();
	b2Body *returnedEntityPhysicsObject = nullptr;
	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (!returnedEntity->staticObject)
		{
			returnedEntityPhysicsObject =  returnedEntity->physicsObject;

			//If the object has a physics object attatched
			if(returnedEntityPhysicsObject != nullptr)
			{
				returnedEntityPhysicsObject->SetLinearVelocity(b2Vec2(returnedEntity->movementVector.x, returnedEntity->movementVector.y));
			}
		}

		while (gameObjects->IsNext())
		{
			returnedEntity = gameObjects->Next();
			if (!returnedEntity->staticObject)
			{
				returnedEntityPhysicsObject = returnedEntity->physicsObject;

				//If the object has a physics object attatched
				if (returnedEntityPhysicsObject != nullptr)
				{
					returnedEntityPhysicsObject->SetLinearVelocity(b2Vec2(returnedEntity->movementVector.x, returnedEntity->movementVector.y));
				}
			}
		}
	}

	//Once all the movement vectors have been updated, run the simulation for a tick (1 tick = 16ms for 60 ticks per second)
	world->Step(16, 1, 1);

	//After simulation is complete, loop through game entities again and update the positions of non-static objects
	returnedEntity = gameObjects->TryToGetFirst();

	if (returnedEntity != nullptr)	//Continue only if there is a returned item (i.e. don't try to do anything if there are no objects in the data structure)
	{
		if (!returnedEntity->staticObject)
		{
			returnedEntityPhysicsObject = returnedEntity->physicsObject;

			//If the object has a physics object attatched
			if (returnedEntityPhysicsObject != nullptr)
			{
				//Store the z position of the vector (i.e. the object's depth within the scene) since the physics is simulated in 2D
				float zPos = returnedEntity->position.z;

				//Transfer the updated location from the physics object back to the game object
				returnedEntity->position = Vector3(returnedEntityPhysicsObject->GetPosition().x, returnedEntityPhysicsObject->GetPosition().y, zPos);

				//Set the game object velocity back to 0 in preparation for next loop
				returnedEntity->movementVector = Vector2(0, 0);
			}
		}

		while (gameObjects->IsNext())
		{
			returnedEntity = gameObjects->Next();
			if (!returnedEntity->staticObject)
			{
				returnedEntityPhysicsObject = returnedEntity->physicsObject;

				//If the object has a physics object attatched
				if (returnedEntityPhysicsObject != nullptr)
				{
					//Store the z position of the vector (i.e. the object's depth within the scene) since the physics is simulated in 2D
					float zPos = returnedEntity->position.z;

					//Transfer the updated location from the physics object back to the game object
					returnedEntity->position = Vector3(returnedEntityPhysicsObject->GetPosition().x, returnedEntityPhysicsObject->GetPosition().y, zPos);

					//Set the game object velocity back to 0 in preparation for next loop
					returnedEntity->movementVector = Vector2(0, 0);
				}
			}
		}
	}

}

