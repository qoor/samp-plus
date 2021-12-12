#include "StdInc.h"

#include "ClientStreamer.h"
#include "ClientStreamElement.h"

ClientStreamElement::ClientStreamElement(ClientStreamer* streamer, int id, bool local) : ClassInit(this), ClientEntity(id, local)
{
	Debug::write("ClientStreamElement 持失切");
	this->streamer = streamer;
	streamRow = NULL;
	streamSector = NULL;
	expDistance = 0.0f;
	streamedIn = false;
	attemptingToStreamIn = false;
	streamReferences = 0;
	streamReferencesScript = 0;
	
	streamer->addElement(this);
	Debug::write("ClientStreamElement 持失切 魁");
}

ClientStreamElement::~ClientStreamElement()
{
	streamer->removeElement(this);
}

void ClientStreamElement::updateStreamPosition(const CVector& position)
{
	streamPosition = position;
	
	streamer->onUpdateStreamPosition(this);
	//manager->onUpdateStreamPosition(this);
}

void ClientStreamElement::internalStreamIn(bool instantly)
{
	if (!streamedIn && !attemptingToStreamIn)
	{
		attemptingToStreamIn = true;

		streamIn(instantly);
	}
}

void ClientStreamElement::internalStreamOut()
{
	if (streamedIn)
	{
		streamOut();

		streamedIn = false;
	}
}

void ClientStreamElement::notifyCreate()
{
	streamedIn = true;
	attemptingToStreamIn = false;
}

void ClientStreamElement::notifyUnableToCreate()
{
	attemptingToStreamIn = false;
}

void ClientStreamElement::addStreamReference(bool script)
{
	unsigned short* refs = (script) ? &streamReferencesScript : &streamReferences;

	if ((*refs) < 0xFFFF)
		(*refs)++;

	if ((streamReferences + streamReferencesScript) == 1)
		streamer->onElementForceStreamIn(this);
}

void ClientStreamElement::removeStreamReference(bool script)
{
	unsigned short* refs = (script) ? &streamReferencesScript : &streamReferences;

	if ((*refs) > 0)
		(*refs)--;

	if ((streamReferences + streamReferencesScript) == 0)
		streamer->onElementForceStreamOut(this);
}

unsigned short ClientStreamElement::getStreamReferences(bool script)
{
	unsigned short* refs = (script) ? &streamReferencesScript : &streamReferences;

	return (*refs);
}

void ClientStreamElement::streamOutForABit()
{
	internalStreamOut();
}

CSphere ClientStreamElement::getWorldBoundingSphere()
{
	return CSphere(getStreamPosition(), 0.0f);
}

static float getBoxDistanceSq(const CVector& position, const CVector& boxCenter, const float* extentMin, const float* extentMax, const CVector** boxAxes)
{
	CVector offset = position - boxCenter;
	float distSq = 0.f;

	for (int i = 0; i < 3; ++i)
	{
		float dot = offset.DotProduct(boxAxes[i]);

		if (dot < extentMin[i])
			distSq += (dot - extentMin[i]) * (dot - extentMin[i]);
		else if (dot > extentMax[i])
			distSq += (dot - extentMax[i]) * (dot - extentMax[i]);
	}

	return distSq;
}

float ClientStreamElement::getDistanceToBoundingBoxSquared(const CVector& position)
{
	if (this == ClientStreamer::addingElement)
		return (getStreamPosition() - position).LengthSquared();

	if (--cachedRadiusCounter < 0)
	{
		StaticFunctionDefinations::getElementRadius(*this, cachedRadius);
		cachedRadiusCounter = 20 + rand() % 50;
	}

	if (cachedRadius < 20)
		return (getStreamPosition() - position).LengthSquared();

	if (--cachedBoundingBoxCounter < 0)
	{
		CVector min;
		CVector max;

		StaticFunctionDefinations::getElementBoundingBox(*this, min, max);

		CVector halfCenter = (min + max) * 0.25f;

		min -= halfCenter;
		max -= halfCenter;

		cachedBoundingBox[0] = min;
		cachedBoundingBox[1] = max;

		cachedBoundingBoxCounter = 20 + rand() % 50;
	}

	const CVector& min = cachedBoundingBox[0];
	const CVector& max = cachedBoundingBox[1];
	CMatrix gtaMatrix;

	getMatrix(gtaMatrix);

	const CVector* boxAxes[3] = { &gtaMatrix.vRight, &gtaMatrix.vFront, &gtaMatrix.vUp };

	return getBoxDistanceSq(position, getStreamPosition(), &min.fX, &max.fX, boxAxes);
}
