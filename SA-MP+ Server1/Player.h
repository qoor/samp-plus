#pragma once

#include "ClientSocketInfo.h"

class Player
{
private:
	ClientSocketInfo* socket;

public:
	Player(ClientSocketInfo* clientSocket) : socket(clientSocket) {}
	inline ClientSocketInfo* getSocket() { return socket; }
};
