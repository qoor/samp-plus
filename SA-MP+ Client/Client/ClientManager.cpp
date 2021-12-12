#include "StdInc.h"

#include "ClientStreamer.h"

ClientManager::ClientManager()
{
	markerStreamer = new ClientStreamer(ClientMarker::isLimitReached, 600.0f, 300, 300);

	markerManager = new ClientMarkerManager();
}

ClientManager::~ClientManager()
{
	delete markerManager;
	markerManager = NULL;

	delete markerStreamer;
	markerStreamer = NULL;
}

void ClientManager::doPulse()
{
	
}

void ClientManager::updateStreamers()
{
	if (isGameLoaded())
	{
		CVector temp;
		CMatrix matResult;
		CCam* cam = game->GetCamera()->GetCam(game->GetCamera()->GetActiveCam());

		if (cam == NULL)
			return;

		game->GetCamera()->GetMatrix(&matResult);

		matResult.vFront = *cam->GetFront();
		matResult.vUp = *cam->GetUp();
		matResult.vPos = *cam->GetSource();
		matResult.vRight = -matResult.vRight;
		matResult.OrthoNormalize(CMatrix::AXIS_FRONT, CMatrix::AXIS_UP);

		temp = matResult.vPos;
		markerStreamer->doPulse(temp);
	}
}

void ClientManager::unreferenceEntity(ClientEntity* entity)
{
	
}
