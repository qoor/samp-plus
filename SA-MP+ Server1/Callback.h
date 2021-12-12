#pragma once

#include "plugin.h"

#include <list>

class Callback
{
private:
	static AMX* allowedAMX;
	static std::list<AMX*> amxPointers;

public:
	enum eCallbackType
	{
		ON_PLAYER_CONNECT,
		ON_PLAYER_DISCONNECT
	};

	struct PAWNArray
	{
		cell* address;
		size_t length;
	};

	static inline std::list<AMX*>& getAMXList() { return amxPointers; }

	static cell execute(const char* function, const char* format, ...);
	static cell process(AMX* amx, eCallbackType callbackType, cell* params);

	static void onPlayerConnect(unsigned int playerid);
	static void onPlayerDisconnect(unsigned int playerid, unsigned short reason);
};
