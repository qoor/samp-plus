#pragma once

#include "ClientMarkerCommon.h"
#include "ClientStreamElement.h"

class ClientMarkerManager;

class ClientMarker : public ClientStreamElement
{
	DECLARE_CLASS(ClientMarker, ClientStreamElement)
private:
	ClientMarkerCommon* marker;
	ClientMarkerManager* markerManager;

	static unsigned int streamedInMarkers;

	void createOfType(int type);

protected:
	void streamIn(bool instantly);
	void streamOut();

public:
	enum eMarkerType
	{
		MARKER_CHECKPOINT,
		MARKER_RING,
		MARKER_CYLINDER,
		MARKER_ARROW,
		MARKER_CORONA,
		MARKER_INVALID = 0xFF
	};

	ClientMarker(class ClientManager* manager, bool isLocal, int markerid, unsigned char type);
	~ClientMarker();

	void unlink();

	void getPosition(CVector& position) const;
	void setPosition(const CVector& position);

	bool setMatrix(const CMatrix& matrix);

	void doPulse();

	eClientEntityType getType() const { return CLIENTMARKER; }

	ClientMarker::eMarkerType getMarkerType() const;
	void setMarkerType(ClientMarker::eMarkerType type);

	class Client3DMarker* get3DMarker();
	class ClientCheckpoint* getCheckpoint();
	class ClientCorona* getCorona();

	bool isVisible() const;
	void setVisible(bool visible);

	SColor getColor() const;
	void setColor(const SColor color);

	float getSize() const;
	void setSize(float size);

	static bool isLimitReached();

	static int stringToType(const char* string);
};
