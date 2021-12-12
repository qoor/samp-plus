#pragma once

#include "ClientMarkerCommon.h"
#include <game/CCheckpoint.h>

class ClientMarker;

class ClientCheckpoint : public ClientMarkerCommon
{
private:
	ClientMarker* thisMarker;
	bool streamedIn;
	CMatrix matrix;
	CVector direction;
	CVector targetPosition;
	bool visible;
	unsigned int icon;
	DWORD type;
	float size;
	SColor color;
	CCheckpoint* checkpoint;

	DWORD id;
	bool isHaveTarget;
	CVector target;

protected:
	bool isStreamedIn() { return streamedIn; }
	void streamIn();
	void streamOut();

public:
	enum
	{
		TYPE_NORMAL,
		TYPE_RING,
		TYPE_INVALID
	};

	enum
	{
		ICON_NONE,
		ICON_ARROW,
		ICON_FINISH
	};

	ClientCheckpoint(ClientMarker* thisMarker);
	~ClientCheckpoint();

	void create(unsigned long id = 0UL);
	void destroy();
	void recreate();

	unsigned int getMarkerType() const { return ClientMarkerCommon::CLASS_CHECKPOINT; }

	unsigned long getCheckpointType() const;
	void setCheckpointType(unsigned long type);

	void getPosition(CVector& position) const { position = matrix.vPos; }
	void setPosition(const CVector& position);
	void setDirection(const CVector& direction);
	void setNextPosition(const CVector& position);

	void getMatrix(CMatrix& matrix);
	void setMatrix(CMatrix& matrix);

	bool isVisible() const { return visible; }
	void setVisible(bool visible);

	unsigned int getIcon() const { return icon; }
	void setIcon(unsigned int icon);

	SColor getColor() const { return color; }
	void setColor(const SColor& color);

	float getSize() const { return size; }
	void setSize(float size);

	bool hasTarget() { return isHaveTarget; }
	void setHasTarget(bool isHaveTarget) { this->isHaveTarget = isHaveTarget; }
	void getTarget(CVector& target) { target = targetPosition; }
	void setTarget(const CVector& target) { targetPosition = target; }

	static unsigned char stringToIcon(const char* string);
	static bool iconToString(unsigned char icon, SString& outString);
	void recreateWithSameIdentifier();
};
