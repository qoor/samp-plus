#pragma once

#include "ClientEntity.h"

class ClientStreamer;
class ClientStreamSector;
class ClientStreamSectorRow;

class ClientStreamElement : public ClientEntity
{
	DECLARE_CLASS(ClientStreamElement, ClientEntity)
	friend class ClientStreamer;

private:
	void setStreamRow(ClientStreamSectorRow* row) { streamRow = row; }
	void setStreamSector(ClientStreamSector* sector) { streamSector = sector; }
	void setExpDistance(float distance) { expDistance = distance; }

	ClientStreamer* streamer;
	ClientStreamSectorRow* streamRow;
	ClientStreamSector* streamSector;
	CVector streamPosition;
	float expDistance;
	unsigned short streamReferences, streamReferencesScript;

protected:
	bool streamedIn;
	bool attemptingToStreamIn;

public:
	float cachedRadius;
	int cachedRadiusCounter;
	SFixedArray<CVector, 2> cachedBoundingBox;
	int cachedBoundingBoxCounter;

	ClientStreamElement(ClientStreamer* streamer, int id, bool local);
	~ClientStreamElement();

	void updateStreamPosition(const CVector& position);
	CVector getStreamPosition() { return streamPosition; }
	ClientStreamSectorRow* getStreamRow() { return streamRow; }
	ClientStreamSector* getStreamSector() { return streamSector; }
	bool isStreamedIn() { return streamedIn; }
	void internalStreamIn(bool instantly);
	void internalStreamOut();
	virtual void streamIn(bool instantly) = 0;
	virtual void streamOut() = 0;
	virtual void notifyCreate();
	void notifyUnableToCreate();
	void addStreamReference(bool script = false);
	void removeStreamReference(bool script = false);
	unsigned short getStreamReferences(bool script = false);
	unsigned long getTotalStreamReferences() { return streamReferences + streamReferencesScript; }
	void streamOutForABit();
	float getExpDistance() { return expDistance; }
	virtual CSphere getWorldBoundingSphere();
	float getDistanceToBoundingBoxSquared(const CVector& position);

	bool isStreamingCompatibleClass() { return true; }
};
