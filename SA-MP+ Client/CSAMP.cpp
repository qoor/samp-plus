#include "StdInc.h"

#include <game_sa/CEntitySA.h>

#include "CSAMPStruct.h"

#define SAMP_DLL		"samp.dll"
#define SAMP03d_CMP		"C70424C97E9C8F442430"
#define SAMP037_CMP		"F8036A004050518D4C24"
#define SAMP03DL_CMP	"528D44240C508D7E09E8"

CSAMP::CSAMP()
{
	version = NULL;
	moduleAddress = NULL;
	sampInterface = NULL;
	chatInfo = NULL;
	inputInfo = NULL;
	killInfo = NULL;
	scoreBoardInfo = NULL;
	localPed = NULL;
	sampStructInitialized = false;
	memset(translateVehiclePool, SAMP_INVALID_VEHICLE_ID, SAMP_MAX_VEHICLES);
	memset(translatePlayerPool, SAMP_INVALID_VEHICLE_ID, SAMP037_MAX_PLAYERS);
}

CSAMP::~CSAMP()
{
	
}

void CSAMP::detectSAMPVersion()
{
	uint32_t* samp_dll = getModuleAddress();

	if (samp_dll == NULL)
	{
		version = NULL;

		Debug::write("SA-MP 모듈을 찾을 수 없습니다.");
	}
	else
	{
		moduleAddress = samp_dll;

		if (memcmp_safe(getPointer<uint8_t*>(0xBABE), hex_to_bin(SAMP03d_CMP), 10))
		{
			version = eSupportVersion::SAMP_03d;

			Debug::write("SA-MP 0.3d 버전이 감지되었습니다.");
		}
		else if (memcmp_safe(getPointer<uint8_t*>(0xBABE), hex_to_bin(SAMP037_CMP), 10))
		{
			version = eSupportVersion::SAMP_037;

			Debug::write("SA-MP 0.3.7 버전이 감지되었습니다.");
		}
		else if (memcmp_safe(getPointer<uint8_t*>(0xBABE), hex_to_bin(SAMP03DL_CMP), 10))
		{
			version = eSupportVersion::SAMP_03DL;

			Debug::write("SA-MP 0.3.7-DL 버전이 감지되었습니다.");
		}
		else
		{
			version = NULL;
			moduleAddress = NULL;

			Debug::write("지원되지 않는 SA-MP 버전입니다.");

			return;
		}

		disableSAMPAntiCheat();
	}
}

uint32_t* CSAMP::getModuleAddress()
{
	return reinterpret_cast<uint32_t*>(GetModuleHandleA(SAMP_DLL));
}

void CSAMP::disableSAMPAntiCheat()
{
	if (!isValidSAMPVersion())
		return;

	Debug::write("+ CSAMP::disableSAMPAntiCheat()");

	if (version == eSupportVersion::SAMP_03d)
	{
		memcpy_safe(getPointer<uint8_t*>(0x24AE16), "\x90\x90\x90\x90\x90\x90", 6);
		memcpy_safe(getPointer<uint8_t*>(0x27B1D3), "\x90\x90\x90\x90\x90\x90", 6);
	}
	else
	{
		static uint32_t anticheat = 1;
		byte acpatch[] = { 0xFF, 0x05, 0x00, 0x00, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xC3 };
		*(uint32_t**)&acpatch[2] = *(uint32_t**)&acpatch[7] = &anticheat;

		if (version == eSupportVersion::SAMP_037)
		{
			memcpy_safe(getPointer<uint8_t*>(0x99250), "\xC3", 1);
			memcpy_safe(getPointer<uint8_t*>(0x286923), "\xB8\x45\x00\x00\x00\xC2\x1C\x00", 8);
			memcpy_safe(getPointer<uint8_t*>(0x298116), "\xB8\x45\x00\x00\x00\xC2\x1C\x00", 8);

			
			memcpy_safe(getPointer<uint8_t*>(0x2B9EE4), acpatch, 12);
		}
		else if (version == eSupportVersion::SAMP_03DL)
		{
			memcpy_safe(getPointer<uint8_t*>(0x9D6F0), "\xC3", 1);
			memcpy_safe(getPointer<uint8_t*>(0xC5C10), "\xB8\x45\x00\x00\x00\xC2\x1C\x00", 8);

			memcpy_safe(getPointer<uint8_t*>(0xC5E2B), acpatch, 12);
		}
	}

	Debug::write("- CSAMP::disableSAMPAntiCheat()");
}

void CSAMP::doPostFramePulse()
{
	if (!isValidSAMPVersion())
		return;

	if (!sampStructInitialized)
	{
		SAMPInputInfo* inputInfo = NULL;
		
		if (version == eSupportVersion::SAMP_03d)
		{
			SAMP03d* sampInterface = getInterfaceAddress<SAMP03d*>(SAMP03d_INFO_OFFSET);

			if (isBadPtr_writeAny(sampInterface, sizeof(SAMP03d)))
				return;

			this->sampInterface = reinterpret_cast<uint32_t*>(sampInterface);

			if (isBadPtr_writeAny(sampInterface->pPools, sizeof(SAMP03dPools)))
				return;

			if (isBadPtr_writeAny(sampInterface->pPools->pPlayer, sizeof(SAMP03dPlayerPool)))
				return;

			if (isBadPtr_writeAny(sampInterface->pPools->pVehicle, sizeof(SAMP03dVehiclePool)))
				return;

			SAMP03dChatInfo* chatInfo = getInterfaceAddress<SAMP03dChatInfo*>(SAMP03d_CHAT_INFO_OFFSET);

			if (isBadPtr_writeAny(chatInfo, sizeof(SAMP03dChatInfo)))
				return;

			this->chatInfo = reinterpret_cast<uint32_t*>(chatInfo);

			SAMP03dKillInfo* killInfo = getInterfaceAddress<SAMP03dKillInfo*>(SAMP03d_KILL_INFO_OFFSET);

			if (isBadPtr_writeAny(killInfo, sizeof(SAMP03dKillInfo)))
				return;

			this->killInfo = reinterpret_cast<uint32_t*>(killInfo);

			if (sampInterface->pRakClientInterface == NULL)
				return;

			inputInfo = getInterfaceAddress<SAMPInputInfo*>(SAMP03d_CHAT_INPUT_INFO_OFFSET);
		}
		else
		{
			SAMP037* sampInterface = NULL;
			SAMP037ChatInfo* chatInfo = NULL;
			SAMP037KillInfo* killInfo = NULL;

			if (version == eSupportVersion::SAMP_037)
			{
				sampInterface = getInterfaceAddress<SAMP037*>(SAMP037_INFO_OFFSET);
				chatInfo = getInterfaceAddress<SAMP037ChatInfo*>(SAMP037_CHAT_INFO_OFFSET);
				killInfo = getInterfaceAddress<SAMP037KillInfo*>(SAMP037_KILL_INFO_OFFSET);
				inputInfo = getInterfaceAddress<SAMPInputInfo*>(SAMP037_CHAT_INPUT_INFO_OFFSET);
			}
			else
			{
				sampInterface = getInterfaceAddress<SAMP037*>(SAMP03DL_INFO_OFFSET);
				chatInfo = getInterfaceAddress<SAMP037ChatInfo*>(SAMP03DL_CHAT_INFO_OFFSET);
				killInfo = getInterfaceAddress<SAMP037KillInfo*>(SAMP03DL_KILL_INFO_OFFSET);
				inputInfo = getInterfaceAddress<SAMPInputInfo*>(SAMP03DL_CHAT_INPUT_INFO_OFFSET);
			}

			if (isBadPtr_writeAny(sampInterface, sizeof(SAMP037)))
				return;

			this->sampInterface = reinterpret_cast<uint32_t*>(sampInterface);

			if (isBadPtr_writeAny(sampInterface->pPools, sizeof(SAMP03dPools)))
				return;

			if (isBadPtr_writeAny(sampInterface->pPools->pPlayer, sizeof(SAMP03dPlayerPool)))
				return;

			if (isBadPtr_writeAny(sampInterface->pPools->pVehicle, sizeof(SAMP03dVehiclePool)))
				return;

			if (isBadPtr_writeAny(chatInfo, sizeof(SAMP037ChatInfo)))
				return;

			this->chatInfo = reinterpret_cast<uint32_t*>(chatInfo);

			if (isBadPtr_writeAny(killInfo, sizeof(SAMP037KillInfo)))
				return;

			this->killInfo = reinterpret_cast<uint32_t*>(killInfo);

			if (sampInterface->pRakClientInterface == NULL)
				return;
		}

		if (isBadPtr_writeAny(inputInfo, sizeof(SAMPInputInfo)))
			return;

		this->inputInfo = reinterpret_cast<uint32_t*>(inputInfo);

		sampStructInitialized = true;

		Debug::write("SA-MP 후킹 완료.");
	}

	if (sampStructInitialized)
	{
		if (localPed == NULL)
			localPed = core->getLocalPed();

		updateTranslateSAMPToGTAEntities();
	}
}

void CSAMP::updateTranslateSAMPToGTAEntities()
{
	CVehicle* vehicle = NULL;
	CPed* ped = NULL;
	CPools* gamePool = core->getGame()->GetPools();
	CVehicleSAInterface* vehicleInterface = NULL;
	CPedSAInterface* pedInterface = NULL;

	if (version == eSupportVersion::SAMP_03d)
	{
		SAMP03dVehiclePool* vehiclePool = reinterpret_cast<SAMP03d*>(sampInterface)->pPools->pVehicle;

		if (vehiclePool == NULL)
			return;

		int i;

		for (i = 0; i < SAMP_MAX_VEHICLES; ++i)
		{
			if (vehiclePool->iIsListed[i] != 1)
				continue;

			if (vehiclePool->pSAMP_Vehicle[i] == nullptr)
				continue;

			vehicleInterface = vehiclePool->pSAMP_Vehicle[i]->pGTA_Vehicle;

			if (vehicleInterface == nullptr)
				continue;

			vehicle = gamePool->GetVehicle((DWORD*)vehicleInterface);

			if (vehicle != NULL && vehicle->GetArrayID() < SAMP_MAX_VEHICLES)
				translateVehiclePool[vehicle->GetArrayID()] = i;
		}

		SAMP03dPlayerPool* playerPool = reinterpret_cast<SAMP03d*>(sampInterface)->pPools->pPlayer;

		if (playerPool == NULL)
			return;

		for (i = 0; i < SAMP03d_MAX_PLAYERS; ++i)
		{
			if (i == playerPool->sLocalPlayerID)
			{
				if (localPed != NULL && localPed->GetArrayID() < SAMP03d_MAX_PLAYERS)
					translatePlayerPool[localPed->GetArrayID()] = i;

				Debug::write("로컬 플레이어 등록 완료.");

				continue;
			}

			if (playerPool->iIsListed[i] != 1)
				continue;
			if (playerPool->pRemotePlayer[i] == nullptr)
				continue;
			if (playerPool->pRemotePlayer[i]->pPlayerData == nullptr)
				continue;
			if (playerPool->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == nullptr)
				continue;

			Debug::write("리모트 플레이어 분석 시작.");

			pedInterface = playerPool->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTA_Ped;

			if (pedInterface == nullptr)
				continue;

			Debug::write("리모트 플레이어 등록.");

			ped = gamePool->GetPed((DWORD*)pedInterface);

			if (ped != NULL && ped->GetArrayID() < SAMP03d_MAX_PLAYERS)
				translatePlayerPool[ped->GetArrayID()] = i;

			Debug::write("리모트 플레이어 등록 완료.");
		}
	}
	else
	{
		SAMP037VehiclePool* vehiclePool = reinterpret_cast<SAMP037*>(sampInterface)->pPools->pVehicle;

		if (vehiclePool == NULL)
			return;

		int i;

		for (i = 0; i < SAMP_MAX_VEHICLES; ++i)
		{
			if (vehiclePool->iIsListed[i] != 1)
				continue;

			if (vehiclePool->pSAMP_Vehicle[i] == nullptr)
				continue;

			vehicleInterface = vehiclePool->pSAMP_Vehicle[i]->pGTA_Vehicle;

			if (vehicleInterface == nullptr)
				continue;

			vehicle = gamePool->GetVehicle((DWORD*)vehicleInterface);

			if (vehicle != NULL && vehicle->GetArrayID() < SAMP_MAX_VEHICLES)
				translateVehiclePool[vehicle->GetArrayID()] = i;
		}

		SAMP037PlayerPool* playerPool = reinterpret_cast<SAMP037*>(sampInterface)->pPools->pPlayer;

		if (playerPool == NULL)
			return;

		for (i = 0; i < SAMP037_MAX_PLAYERS; ++i)
		{
			if (i == playerPool->sLocalPlayerID)
			{
				ped = core->getLocalPed();

				if (ped != NULL && ped->GetArrayID() < SAMP03d_MAX_PLAYERS)
					translatePlayerPool[ped->GetArrayID()] = i;

				continue;
			}

			if (playerPool->iIsListed[i] != 1)
				continue;
			if (playerPool->pRemotePlayer[i] == nullptr)
				continue;
			if (playerPool->pRemotePlayer[i]->pPlayerData == nullptr)
				continue;
			if (playerPool->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == nullptr)
				continue;

			pedInterface = playerPool->pRemotePlayer[i]->pPlayerData->pSAMP_Actor->pGTAEntity;

			if (pedInterface == nullptr)
				continue;

			ped = gamePool->GetPed((DWORD*)pedInterface);

			if (ped != NULL && ped->GetArrayID() < SAMP037_MAX_PLAYERS)
				translatePlayerPool[ped->GetArrayID()] = i;
		}
	}
}

int CSAMP::getVehicleIdFromVehicleInterface(CVehicleSAInterface* targetInterface)
{
	if (targetInterface != NULL)
	{
		CVehicle* vehicle = core->getGame()->GetPools()->GetVehicle((DWORD*)targetInterface);

		if (vehicle != NULL)
		{
			int poolId = vehicle->GetArrayID();

			if (poolId < SAMP_MAX_VEHICLES)
				return translateVehiclePool[poolId];
		}
	}

	return SAMP_INVALID_VEHICLE_ID;
}

int CSAMP::getPlayerIdFromPedInterface(CPedSAInterface* targetInterface)
{
	if (targetInterface != NULL)
	{
		CPed* ped = core->getGame()->GetPools()->GetPed((DWORD*)targetInterface);

		if (ped != NULL)
		{
			int poolId = ped->GetArrayID();

			if (poolId < SAMP037_MAX_PLAYERS)
				return translatePlayerPool[poolId];
		}
	}

	return SAMP_INVALID_PLAYER_ID;
}

CVehicleSAInterface* CSAMP::getVehicleInterfaceFromVehicleId(int vehicleid)
{
	if (vehicleid < 0 || vehicleid >= SAMP_MAX_VEHICLES)
		return NULL;

	int currentVehicleId = SAMP_INVALID_VEHICLE_ID;

	if (version == eSupportVersion::SAMP_03d)
		currentVehicleId = reinterpret_cast<SAMP03d*>(sampInterface)->pPools->pPlayer->pLocalPlayer->sCurrentVehicleID;
	else
		currentVehicleId = reinterpret_cast<SAMP037*>(sampInterface)->pPools->pPlayer->pLocalPlayer->sCurrentVehicleID;

	if (vehicleid == currentVehicleId)
	{
		if (localPed != NULL && currentVehicleId < SAMP_INVALID_VEHICLE_ID)
		{
			CVehicle* vehicle = localPed->GetVehicle();

			if (vehicle != NULL)
				return static_cast<CVehicleSAInterface*>(vehicle->GetInterface());
		}
	}
	else
	{
		CVehicleSAInterface* vehicleInterface = NULL;

		if (version == eSupportVersion::SAMP_03d)
			vehicleInterface = reinterpret_cast<SAMP03d*>(sampInterface)->pPools->pVehicle->pGTA_Vehicle[vehicleid];
		else
			vehicleInterface = reinterpret_cast<SAMP037*>(sampInterface)->pPools->pVehicle->pGTA_Vehicle[vehicleid];

		if (core->getGame()->GetPools()->GetVehicle(reinterpret_cast<DWORD*>(vehicleInterface)) != NULL)
			return vehicleInterface;
	}

	return NULL;
}

CPedSAInterface* CSAMP::getPedInterfaceFromPlayerId(int playerid)
{
	if (playerid < 0 || playerid >= SAMP037_MAX_PLAYERS)
		return NULL;

	CPedSAInterface* returnPed = NULL;

	if (version == eSupportVersion::SAMP_03d)
	{
		SAMP03dPlayerPool* playerPool = reinterpret_cast<SAMP03d*>(sampInterface)->pPools->pPlayer;

		if (playerPool == NULL)
			return NULL;

		if (playerPool->iIsListed[playerid] != 1)
			return NULL;
		if (playerPool->pRemotePlayer[playerid] == NULL)
			return NULL;
		if (playerPool->pRemotePlayer[playerid]->pPlayerData == NULL)
			return NULL;
		if (playerPool->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == NULL)
			return NULL;

		returnPed = playerPool->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTA_Ped;
	}
	else
	{
		SAMP037PlayerPool* playerPool = reinterpret_cast<SAMP037*>(sampInterface)->pPools->pPlayer;

		if (playerPool == NULL)
			return NULL;

		if (playerPool->iIsListed[playerid] != 1)
			return NULL;
		if (playerPool->pRemotePlayer[playerid] == NULL)
			return NULL;
		if (playerPool->pRemotePlayer[playerid]->pPlayerData == NULL)
			return NULL;
		if (playerPool->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor == NULL)
			return NULL;

		returnPed = playerPool->pRemotePlayer[playerid]->pPlayerData->pSAMP_Actor->pGTAEntity;
	}

	if (core->getGame()->GetPools()->GetPed(reinterpret_cast<DWORD*>(returnPed)) == NULL)
		returnPed = NULL;

	return returnPed;
}
