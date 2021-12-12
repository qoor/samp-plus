#pragma once

#include "Element.h"

enum ePedMoveAnim
{
	MOVE_DEFAULT = 0,
	MOVE_PLAYER = 54,
	MOVE_PLAYER_F,
	MOVE_PLAYER_M,
	MOVE_ROCKET,
	MOVE_ROCKET_F,
	MOVE_ROCKET_M,
	MOVE_ARMED,
	MOVE_ARMED_F,
	MOVE_ARMED_M,
	MOVE_BBBAT,
	MOVE_BBBAT_F,
	MOVE_BBBAT_M,
	MOVE_CSAW,
	MOVE_CSAW_F,
	MOVE_CSAW_M,
	MOVE_SNEAK,
	MOVE_JETPACK,
	MOVE_MAN = 118,
	MOVE_SHUFFLE,
	MOVE_OLDMAN,
	MOVE_GANG1,
	MOVE_GANG2,
	MOVE_OLDFATMAN,
	MOVE_FATMAN,
	MOVE_JOGGER,
	MOVE_DRUNKMAN,
	MOVE_BLINDMAN,
	MOVE_SWAT,
	MOVE_WOMAN,
	MOVE_SHOPPING,
	MOVE_BUSYWOMAN,
	MOVE_SEXYWOMAN,
	MOVE_PRO,
	MOVE_OLDWOMAN,
	MOVE_FATWOMAN,
	MOVE_JOGWOMAN,
	MOVE_OLDFATWOMAN,
	MOVE_SKATE,
};

class PedManager;

class Ped : public Element
{
	friend class Element;

private:
	PedManager* pedManager;

protected:
	bool wearingGoggles;
	bool inWater;
	bool onGround;
	bool player;
	unsigned char alpha;
	float gravity;
	bool headLess;
	bool frozen;
	unsigned char moveAnim;

	bool collisionsEnabled;

public:
	Ped(PedManager* pedManager, unsigned int playerid);
	~Ped();

	bool isEntity() { return true; }

	virtual void unlink();

	bool isPlayer() { return player; }

	bool isWearingGoggles() { return wearingGoggles; }
	void setWearingGoggles(bool wearingGoggles) { this->wearingGoggles = wearingGoggles; }

	bool isInWater() { return inWater; }
	void setInWater(bool inWater) { this->inWater; }

	bool isOnGround() { return onGround; }
	void setOnGround(bool onGround) { this->onGround = onGround; }

	unsigned char getAlpha() { return alpha; }
	void setAlpha(unsigned char alpha) { this->alpha = alpha; }

	unsigned char getMoveAnim() { return moveAnim; }
	void setMoveAnim(unsigned char moveAnim) { this->moveAnim = moveAnim; }

	float getGravity() { return gravity; }
	void setGravity(float gravity) { this->gravity = gravity; }

	bool isHeadless() { return headLess; }
	void setHeadless(bool headLess) { this->headLess = headLess; }

	bool isFrozen() { return frozen; }
	void setFrozen(bool frozen) { this->frozen = frozen; }

	bool getCollisionEnabled() { return collisionsEnabled; }
	void setCollisionEnabled(bool collisionEnabled) { this->collisionsEnabled = collisionEnabled; }
};
