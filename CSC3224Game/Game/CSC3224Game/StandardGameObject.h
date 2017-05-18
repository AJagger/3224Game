#pragma once
#include <string>
#include "../../Core/GameObject.h"

enum GameEntityType
{
	STATIC_OBJECT = 0,
	NPC = 1,
	PLAYER = 2,
	PROJECTILE = 3,
	EFFECT = 4,
	UNINITIALISED = 5
};

enum WeaponSelection
{
	NO_WEAPON_SELECTED = 0,
	BC304_RAILGUN = 1
};

class StandardGameObject : public GameObject
{
public:
	StandardGameObject();
	StandardGameObject(GameEntityType type, int meshId, int textureId = 0);
	~StandardGameObject();

	GameEntityType entityType = UNINITIALISED;		
	bool hasTarget = false;							// hasTarget &
	int targetObjectId = -1;						// targetObjectId used for NPCs & Projectiles
	WeaponSelection weapon = NO_WEAPON_SELECTED;	// weapon selection for AI and player ships
	int lifeTime = 0;								// lifeTime used for Effects

	bool markedForDeletion = false;
	int health = 1000;

	unsigned int wep1LastFire = 0;

	void ConfigureDefaultStatic(int meshId, int textureId = 0);
	void ConfigureDefaultNPC(int meshId, int textureId = 0);
	void ConfigureDefaultPlayer(int meshId, int textureId = 0);
	void ConfigureDefaultProjectile(int meshId, int textureId = 0);
	void ConfigureDefaultEffect(int meshId, int textureId = 0);

};