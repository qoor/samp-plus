#pragma once

#include <ctime>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakString.h>

enum eClientConnectionState;

class ClientSocketInfo
{
public:
	enum eClientConnectionState
	{
		AWAITING,
		CONNECTED,
		JOINED
	};

private:
	RakNet::SystemAddress address;
	RakNet::RakNetGUID guid;
	int clientIntVersion;
	RakNet::RakString clientStringVersion;
	eClientConnectionState clientState;
	time_t creationTime;

public:
	ClientSocketInfo(RakNet::SystemAddress address, RakNet::RakNetGUID guid, int clientIntVersion, RakNet::RakString clientStringVersion) : address(address), guid(guid), clientIntVersion(clientIntVersion), clientStringVersion(clientStringVersion), clientState(AWAITING), creationTime(std::time(NULL)) {}

	inline eClientConnectionState getState() { return clientState; }
	inline void setState(eClientConnectionState newState) { clientState = newState; }
	inline RakNet::SystemAddress& getAddress() { return address; }
	inline RakNet::RakNetGUID& getGUID() { return guid; }
	inline const char* getClientVersionString() { return clientStringVersion.C_String(); }
	inline int getClientVersionInt() { return clientIntVersion; }
	inline time_t getCreationTime() { return creationTime; }
};
