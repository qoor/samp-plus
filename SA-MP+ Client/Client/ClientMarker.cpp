#include "StdInc.h"

#include "ClientMarker.h"
#include "ClientCheckpoint.h"
#include "Client3DMarker.h"
#include "ClientCorona.h"
#include "ClientMarkerManager.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

unsigned int ClientMarker::streamedInMarkers = 0;

ClientMarker::ClientMarker(ClientManager* manager, bool isLocal, int markerid, unsigned char type) : ClassInit(this), ClientStreamElement(manager->getMarkerStreamer(), id, isLocal)
{
	marker = NULL;
	markerManager = manager->getMarkerManager();

	createOfType(type);

	markerManager->addToList(this);
}

ClientMarker::~ClientMarker()
{
	unlink();

	manager->unreferenceEntity(this);

	streamOut();

	if (marker != NULL)
	{
		delete marker;
		marker = NULL;
	}
}

void ClientMarker::unlink()
{
	markerManager->removeFromList(this);
}

void ClientMarker::createOfType(int type)
{
	CVector origin;

	getPosition(origin);

	switch (type)
	{
	case MARKER_CHECKPOINT:
	{
		ClientCheckpoint* checkpoint = new ClientCheckpoint(this);

		checkpoint->setCheckpointType(ClientCheckpoint::TYPE_NORMAL);
		marker = checkpoint;
		break;
	}

	case MARKER_RING:
	{
		ClientCheckpoint* checkpoint = new ClientCheckpoint(this);

		checkpoint->setCheckpointType(ClientCheckpoint::TYPE_RING);
		marker = checkpoint;
		break;
	}

	case MARKER_CYLINDER:
	{
		Client3DMarker* marker3D = new Client3DMarker(this);

		marker3D->set3DMarkerType(Client3DMarker::TYPE_CYLINDER);
		marker = marker3D;
		break;
	}
		
	case MARKER_ARROW:
	{
		Client3DMarker* marker3D = new Client3DMarker(this);

		marker3D->set3DMarkerType(Client3DMarker::TYPE_ARROW);
		marker = marker3D;
		break;
	}

	case MARKER_CORONA:
	{
		marker = new ClientCorona(this);
		break;
	}

	default:
		break;
	}
}

void ClientMarker::getPosition(CVector& position) const
{
	if (marker != NULL)
		marker->getPosition(position);
	else
		position = CVector();
}

void ClientMarker::setPosition(const CVector& position)
{
	if (marker != NULL)
		marker->setPosition(position);
	
	updateStreamPosition(position);
}

bool ClientMarker::setMatrix(const CMatrix& matrix)
{
	if (marker != NULL)
		marker->setMatrix(const_cast<CMatrix&>(matrix));

	updateStreamPosition(matrix.vPos);

	return true;
}

void ClientMarker::doPulse()
{
	if (marker != NULL)
		marker->doPulse();
}

ClientMarker::eMarkerType ClientMarker::getMarkerType() const
{
	unsigned int markerType = marker->getMarkerType();

	switch (markerType)
	{
	case ClientMarkerCommon::CLASS_CHECKPOINT:
	{
		unsigned long checkpointType = static_cast<ClientCheckpoint*>(marker)->getCheckpointType();

		if (checkpointType == ClientCheckpoint::TYPE_NORMAL)
			return MARKER_CHECKPOINT;
		else
			return MARKER_RING;
	}

	case ClientMarkerCommon::CLASS_3DMARKER:
	{
		unsigned long type3D = static_cast<Client3DMarker*>(marker)->get3DMarkerType();

		if (type3D == Client3DMarker::TYPE_CYLINDER)
			return MARKER_CYLINDER;
		else
			return MARKER_ARROW;
	}

	case ClientMarkerCommon::CLASS_CORONA:
	{
		return MARKER_CORONA;
	}
	}

	return MARKER_INVALID;
}

void ClientMarker::setMarkerType(ClientMarker::eMarkerType type)
{
	// Different from current type?
	eMarkerType currentType = getMarkerType();

	if (currentType != type)
	{
		// Current type is a checkpoint and new type is a ring?
		if (currentType == MARKER_CHECKPOINT && type == MARKER_RING)
		{
			// Just change the type
			static_cast<ClientCheckpoint*>(marker)->setCheckpointType(ClientCheckpoint::TYPE_RING);
		}

		// Or current type is a ring and new type is a checkpoint?
		if (currentType == MARKER_RING && type == MARKER_CHECKPOINT)
		{
			// Just change the type
			static_cast<ClientCheckpoint*>(marker)->setCheckpointType(ClientCheckpoint::TYPE_NORMAL);
		}

		// Current type is a cylinder and new type is an arrow
		if (currentType == MARKER_CYLINDER && type == MARKER_ARROW)
		{
			// Just change the type
			static_cast<Client3DMarker*>(marker)->set3DMarkerType(Client3DMarker::TYPE_ARROW);
		}

		// Current type is an arrow and new type is an cylinder
		if (currentType == MARKER_ARROW && type == MARKER_CYLINDER)
		{
			// Just change the type
			static_cast<Client3DMarker*>(marker)->set3DMarkerType(Client3DMarker::TYPE_CYLINDER);
		}

		// No easy way of changing the type. Different classes. Remember position and color and recreate it.
		CVector vecPosition;

		marker->getPosition(vecPosition);

		bool   bVisible = marker->isVisible();
		float  fSize = marker->getSize();
		SColor color = marker->getColor();
		bool   bStreamedIn = isStreamedIn();

		// Destroy the old.
		delete marker;
		marker = NULL;

		// Create a new one of the correct type
		createOfType(type);

		// Set the properties back
		setPosition(vecPosition);
		setSize(fSize);
		setColor(color);
		setVisible(bVisible);

		// Stream it in if it was streamed in
		if (bStreamedIn)
			marker->streamIn();
	}
}

Client3DMarker* ClientMarker::get3DMarker()
{
	if (marker->getMarkerType() == ClientMarkerCommon::CLASS_3DMARKER)
		return static_cast<Client3DMarker*>(marker);

	return NULL;
}

ClientCheckpoint* ClientMarker::getCheckpoint()
{
	if (marker->getMarkerType() == ClientMarkerCommon::CLASS_CHECKPOINT)
		return static_cast<ClientCheckpoint*>(marker);

	return NULL;
}

ClientCorona* ClientMarker::getCorona()
{
	if (marker->getMarkerType() == ClientMarkerCommon::CLASS_CORONA)
		return static_cast<ClientCorona*>(marker);

	return NULL;
}

bool ClientMarker::isVisible() const
{
	return marker->isVisible();
}

void ClientMarker::setVisible(bool visible)
{
	marker->setVisible(visible);
}

SColor ClientMarker::getColor() const
{
	return marker->getColor();
}

void ClientMarker::setColor(const SColor color)
{
	marker->setColor(color);
}

float ClientMarker::getSize() const
{
	return marker->getSize();
}

void ClientMarker::setSize(float size)
{
	marker->setSize(size);
}

bool ClientMarker::isLimitReached()
{
	return streamedInMarkers >= 32;
}

void ClientMarker::streamIn(bool instantly)
{
	if (!isStreamedIn())
	{
		marker->streamIn();

		++streamedInMarkers;

		notifyCreate();
	}
}

void ClientMarker::streamOut()
{
	if (isStreamedIn())
	{
		--streamedInMarkers;

		marker->streamOut();
	}
}

int ClientMarker::stringToType(const char* string)
{
	if (stricmp(string, "default") == 0 || stricmp(string, "checkpoint") == 0)
		return MARKER_CHECKPOINT;
	else if (stricmp(string, "ring") == 0)
		return MARKER_RING;
	else if (stricmp(string, "cylinder") == 0)
		return MARKER_CYLINDER;
	else if (strcmp(string, "arrow") == 0)
		return MARKER_ARROW;
	else if (strcmp(string, "corona") == 0)
		return MARKER_CORONA;

	return MARKER_INVALID;
}
