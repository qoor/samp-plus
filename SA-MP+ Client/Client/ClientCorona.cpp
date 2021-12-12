#include "StdInc.h"

#include "ClientMarkerCommon.h"
#include "ClientCorona.h"

ClientCorona::ClientCorona(ClientMarker* thisMarker)
{
	this->thisMarker = thisMarker;
	streamedIn = false;
	visible = true;
	color = SColorRGBA(255, 0, 0, 255);
	size = 4.0f;
	coronas = game->GetCoronas();

	static unsigned long id = 0xFFFFFFFF;

	this->id = --id;
}

ClientCorona::~ClientCorona()
{
	CRegisteredCorona* corona = coronas->CreateCorona(id, &matrix.vPos);

	if (corona)
		corona->Disable();
}

void ClientCorona::streamIn()
{
	streamedIn = true;
}

void ClientCorona::streamOut()
{
	CRegisteredCorona* corona = coronas->CreateCorona(id, &matrix.vPos);

	if (corona)
		corona->Disable();

	streamedIn = false;
}

void ClientCorona::doPulse()
{
	CRegisteredCorona* corona = coronas->CreateCorona(id, &matrix.vPos);

	if (!corona)
		return;

	if (isStreamedIn() && visible)
	{
		SColor color = getColor();

		corona->SetColor(color.R, color.G, color.B, color.A);
		corona->SetSize(size);
	}
	else
		corona->Disable();
}
