#include "StdInc.h"

#include "Client3DMarker.h"

Client3DMarker::Client3DMarker(ClientMarker* thisMarker)
{
	this->thisMarker = thisMarker;
	markerStreamedIn = false;
	visible = true;
	color = SColorRGBA(255, 0, 0, 128);
	size = 4.0f;
	type = MARKER3D_CYLINDER2;
	marker = NULL;
	id = (DWORD)this;
}

Client3DMarker::~Client3DMarker()
{

}

unsigned long Client3DMarker::get3DMarkerType()
{
	switch (type)
	{
	case MARKER3D_CYLINDER2:
		return Client3DMarker::TYPE_CYLINDER;

	case MARKER3D_ARROW:
		return Client3DMarker::TYPE_ARROW;

	default:
		return Client3DMarker::TYPE_INVALID;
	}
}

void Client3DMarker::set3DMarkerType(unsigned long type)
{
	switch (type)
	{
	case Client3DMarker::TYPE_CYLINDER:
		this->type = MARKER3D_CYLINDER2;
		break;

	case Client3DMarker::TYPE_ARROW:
		this->type = MARKER3D_ARROW;
		break;

	default:
		this->type = MARKER3D_CYLINDER2;
		break;
	}
}

void Client3DMarker::streamIn()
{
	markerStreamedIn = true;
}

void Client3DMarker::streamOut()
{
	markerStreamedIn = false;
	marker = NULL;
}

void Client3DMarker::doPulse()
{
	if (markerStreamedIn && visible)
	{
		SColor color = getColor();

		marker = game->Get3DMarkers()->CreateMarker(id, static_cast<e3DMarkerType>(type), &matrix.vPos, size, 0.2f, color.R, color.G, color.B, color.A);

		if (marker)
		{
			marker->SetActive();
			marker->SetColor(this->color);
			marker->SetSize(size);
			marker->SetMatrix(&matrix);

			game->GetVisibilityPlugins()->SetClumpAlpha((RpClump*)marker->GetRwObject(), this->color.A);
		}
	}
}
