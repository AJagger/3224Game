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
