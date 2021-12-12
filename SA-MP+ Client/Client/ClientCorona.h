#pragma once

#include "ClientMarker.h"

class ClientCorona : public ClientMarkerCommon
{
private:
	ClientMarker* thisMarker;
	bool streamedIn;
	unsigned long id;
	CMatrix matrix;
	bool visible;
	float size;
	SColor color;
	CCoronas* coronas;

protected:
	bool isStreamedIn() { return streamedIn; }
	void streamIn();
	void streamOut();

	void doPulse();

public:
	ClientCorona(ClientMarker* thisMarker);
	~ClientCorona();

	unsigned int getMarkerType() const { return ClientMarkerCommon::CLASS_CORONA; }

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
};
