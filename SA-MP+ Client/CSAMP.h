#pragma once

#include "CSAMPStruct.h"

class CSAMP
{
private:
	enum eSupportVersion
	{
		SAMP_03d = 1,
		SAMP_037,
		SAMP_03DL
	};

	int version;
	uint32_t* moduleAddress;
	uint32_t* sampInterface;
	uint32_t* chatInfo;
	uint32_t* inputInfo;
	uint32_t* killInfo;
	uint32_t* scoreBoardInfo;
	CPlayerPed* localPed;
	bool sampStructInitialized;
	int translateVehiclePool[SAMP_MAX_VEHICLES];
	int translatePlayerPool[SAMP037_MAX_PLAYERS];

public:
	CSAMP();
	~CSAMP();

	inline bool isValidSAMPVersion() { return (version != NULL && moduleAddress != NULL); }
	void detectSAMPVersion();
	uint32_t* getModuleAddress();
	template <typename T>
	inline T getPointer(uint32_t offset)
	{
		if (moduleAddress == NULL)
			return NULL;

		return (T)(uint8_t*)moduleAddress + offset;
	}
	template <typename T>
	inline T getInterfaceAddress(uint32_t offset)
	{
		if (moduleAddress == NULL)
			return NULL;

		return *(T*)((uint8_t*)moduleAddress + offset);
	}
	void disableSAMPAntiCheat();
	void doPostFramePulse();
	void updateTranslateSAMPToGTAEntities();
	int getVehicleIdFromVehicleInterface(CVehicleSAInterface* targetInterface);
	int getPlayerIdFromPedInterface(CPedSAInterface* targetInterface);
	CVehicleSAInterface* getVehicleInterfaceFromVehicleId(int vehicleid);
	CPedSAInterface* getPedInterfaceFromPlayerId(int playerid);
};
