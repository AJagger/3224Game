#include "stdafx.h"
#include "CustContactListener.h"
#include "Dynamics/Contacts/b2Contact.h"
#include "../Game/CSC3224Game/StandardGameObject.h"
#include "../Game/CSC3224Game/GameRules.h"

CustContactListener::CustContactListener()
{
}


CustContactListener::~CustContactListener()
{
}

void CustContactListener::BeginContact(b2Contact* contact)
{
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	//Check to see that both objects have userData
	if (bodyAUserData && bodyBUserData)
	{
		//Cast the userData back to GameObjects
		StandardGameObject* objA = static_cast<StandardGameObject*>(bodyAUserData);
		StandardGameObject* objB = static_cast<StandardGameObject*>(bodyBUserData);

		//Check for the types of objects
		//First, deal with projectiles
		if(objA->entityType == PROJECTILE || objB->entityType == PROJECTILE)
		{
			//If other object is the player
			if (objA->entityType == PLAYER || objB->entityType == PLAYER)
			{
				//If projectile is hostile, call associated GameRule. If not, ignore the collision
				if((objA->entityType == PROJECTILE && objA->hostile) || (objB->entityType == PROJECTILE && objB->hostile))
				{
					objA->entityType == PROJECTILE ? objA->markedForDeletion = true : objB->markedForDeletion = true;
					objA->entityType == PROJECTILE ? GameRules::Damage(objA, objB) : GameRules::Damage(objB, objA);
				}
				else
				{
					contact->SetEnabled(false);
				}
			}
			//If other object is also a projectile
			else if(objA->entityType == PROJECTILE && objB->entityType == PROJECTILE)
			{
				contact->SetEnabled(false);
			}
			//If other object is an NPC
			else if(objA->entityType == NPC || objB->entityType == NPC)
			{
				//If both entities are hostile then ignore the collision
				if(objA->hostile && objB->hostile)
				{
					contact->SetEnabled(false);
				}
				else
				{
					objA->entityType == PROJECTILE ? objA->markedForDeletion = true : objB->markedForDeletion = true;
					objA->entityType == PROJECTILE ? GameRules::Damage(objA, objB) : GameRules::Damage(objB, objA);
				}
			}
			//Else
			else 
			{
				objA->entityType == PROJECTILE ? objA->markedForDeletion = true : objB->markedForDeletion = true;
				objA->entityType == PROJECTILE ? GameRules::Damage(objA, objB) : GameRules::Damage(objB, objA);
			}
		}
	}

}

void CustContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	//Check to see that both objects have userData
	if (bodyAUserData && bodyBUserData)
	{
		//Cast the userData back to GameObjects
		StandardGameObject* objA = static_cast<StandardGameObject*>(bodyAUserData);
		StandardGameObject* objB = static_cast<StandardGameObject*>(bodyBUserData);

		//Check for the types of objects
		//First, deal with projectiles
		if (objA->entityType == PROJECTILE || objB->entityType == PROJECTILE)
		{
			//If other object is the player
			if (objA->entityType == PLAYER || objB->entityType == PLAYER)
			{
				//If projectile is not hostile, ignore the collision
				if (!((objA->entityType == PROJECTILE && objA->hostile) || (objB->entityType == PROJECTILE && objB->hostile)))
				{
					contact->SetEnabled(false);
				}
			}
			//If other object is also a projectile
			else if (objA->entityType == PROJECTILE && objB->entityType == PROJECTILE)
			{
				contact->SetEnabled(false);
			}
		}
	}
}
