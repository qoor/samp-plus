#include "StdInc.h"

Ped::Ped(PedManager* pedManager, unsigned int playerid) : Element(playerid)
{
	this->pedManager = pedManager;

	wearingGoggles = false;

	headLess = false;
	inWater = false;
	onGround = true;
	player = true;
	frozen = false;

	alpha = 255;

	moveAnim = MOVE_DEFAULT;
	gravity = 0.008f;

	collisionsEnabled = true;

	if (pedManager != NULL)
		pedManager->addToList(this);
}

Ped::~Ped()
{
	unlink();
}

void Ped::unlink()
{
	if (pedManager != NULL)
		pedManager->removeFromList(this);
}