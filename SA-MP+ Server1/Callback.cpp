#include "Callback.h"
#include "Core.h"

AMX* Callback::allowedAMX = NULL;
std::list<AMX*> Callback::amxPointers;

cell Callback::execute(const char* function, const char* format, ...)
{
	cell returnValue = 1;
	cell* returnValuesArray = new cell[amxPointers.size()];
	size_t index = 0;
	va_list args;
	AMX* thisAMX = NULL;
	int functionIndex;
	unsigned int addressIndex;

	std::fill_n(returnValuesArray, amxPointers.size(), 1);

	for (std::list<AMX*>::iterator it = amxPointers.begin(); it != amxPointers.end(); ++it, ++index)
	{
		thisAMX = *it;
		functionIndex = 0;
		
		if (amx_FindPublic(thisAMX, function, &functionIndex) != 0)
			continue;

		cell address[16];

		addressIndex = 0;

		if (format != NULL)
		{
			va_start(args, format);

			for (unsigned int i = 0, size = strlen(format); i < size; ++i)
			{
				switch (format[i])
				{
				case 'i':
					amx_Push(thisAMX, va_arg(args, int));
					break;

				case 's':
					amx_PushString(thisAMX, &address[addressIndex++], NULL, va_arg(args, char*), false, false);
					break;

				case 'a':
					cell amxAddress;
					cell* physicalAddress;
					PAWNArray pawnArray = va_arg(args, PAWNArray);

					amx_Allot(thisAMX, pawnArray.length, &amxAddress, &physicalAddress);
					memcpy(physicalAddress, pawnArray.address, pawnArray.length * sizeof(cell));
					amx_Push(thisAMX, amxAddress);

					break;
				}
			}

			va_end(args);
		}

		amx_Exec(thisAMX, &returnValuesArray[index], functionIndex);

		for (unsigned int i = 0; i < addressIndex; ++i)
			amx_Release(thisAMX, address[i]);
	}

	for (size_t i = 0; i < index; ++i)
	{
		if (returnValuesArray[i] == 0)
			returnValue = 0;
	}

	delete returnValuesArray;

	return returnValue;
}

cell Callback::process(AMX* amx, eCallbackType callbackType, cell* params)
{
	if (allowedAMX == NULL)
		allowedAMX = amx;
	else if (allowedAMX != amx)
		return 0;

	switch (callbackType)
	{
	case ON_PLAYER_CONNECT:
	{
		cell* playerid;

		amx_GetAddr(amx, params[0], &playerid);

		onPlayerConnect(*playerid);

		break;
	}
	case ON_PLAYER_DISCONNECT:
	{
		cell* playerid;
		cell* reason;

		amx_GetAddr(amx, params[0], &playerid);
		amx_GetAddr(amx, params[1], &reason);

		onPlayerDisconnect(*playerid, *reason);

		break;
	}
	}

	return 1;
}

void Callback::onPlayerConnect(unsigned int playerid)
{
	Network* network = core->getNetwork();
	Player* player = network->handleConnection(playerid);
	const char* clientStringVersion;

	if (player != NULL)
	{
		network->sendPlayerPacketEasy(PacketType::ePacketType::PACKET_PLAYER_REGISTERED, playerid);

		clientStringVersion = player->getSocket()->getClientVersionString();
	}
	else
		clientStringVersion = "";

	if (execute("OnPlayerSAMPPlusJoin", "sii", clientStringVersion, network->isPlayerConnected(playerid), playerid))
	{
		Debug::write("플레이어 id: %i (이)가 성공적으로 SA-MP+ 서버에 연결 됨.", playerid);
	}
	else
	{
		if (player != NULL)
			network->destroyPlayerConnection(playerid, true);
	}
}

void Callback::onPlayerDisconnect(unsigned int playerid, unsigned short reason)
{
	Network* network = core->getNetwork();

	if (network->isPlayerConnected(playerid))
	{
		network->destroyPlayerConnection(playerid, (reason >= 2));

		Debug::write("플레이어 id: %i (이)가 접속이 종료 됨. 이유: %s", playerid, (reason == 1) ? ("정상종료") : (reason == 2) ? ("킥/밴") : ("타임아웃"));
	}
}
