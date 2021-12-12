#pragma once

#include "ClientMarkerCommon.h"
#include <game/C3DMarker.h>

class ClientMarker;

class Client3DMarker : public ClientMarkerCommon
{
private:
	ClientMarker* thisMarker;
	CMatrix matrix;

	bool visible;
	DWORD type;
	float size;
	SColor color;
	C3DMarker* marker;
	unsigned int id;
	bool markerStreamedIn;

protected:
	void streamIn();
	void streamOut();

	void doPulse();

public:
	enum
	{
		TYPE_CYLINDER,
		TYPE_ARROW,
		TYPE_INVALID
	};

	Client3DMarker(ClientMarker* thisMarker);
	~Client3DMarker();

	unsigned int getMarkerType() const { return ClientMarkerCommon::CLASS_3DMARKER; }

	unsigned long get3DMarkerType();
	void set3DMarkerType(unsigned long type);

	//bool isHit(const CVector& vecPosition) const;

	void getPosition(CVector& position) const { position = matrix.vPos; }
	void setPosition(const CVector& position) { matrix.vPos = position; }

	void getMatrix(CMatrix& matrix) { matrix = this->matrix; }
	void setMatrix(CMatrix& matrix) { this->matrix = matrix; }

	bool isVisible() const { return visible; }
	void setVisible(bool visible) { this->visible = visible; }

	SColor getColor() const { return color; }
	void setColor(const SColor& color) { this->color = color; }

	float getSize() const { return size; }
	void setSize(float size) { this->size = size; }

	float getPulseFraction() { return static_cast<float>(marker->GetPulseFraction()); }
	void setPulseFraction(float fraction) { marker->SetPulseFraction(fraction); }
};
