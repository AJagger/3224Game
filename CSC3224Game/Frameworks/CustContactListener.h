/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class is used with Box2D to listen for detected collisions so that game rules can be executed on collision. It contains a small amount of game logic pertaining to which game rules
* should be called given the object types involved in the collision.
*/

#pragma once
#include "Dynamics/b2WorldCallbacks.h"

class CustContactListener : public b2ContactListener
{
public:
	CustContactListener();
	~CustContactListener();

	void BeginContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;


};
