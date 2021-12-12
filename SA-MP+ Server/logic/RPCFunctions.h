#pragma once

class Player;
class Game;

#define DECLARE_RPC(a) static void a(RakNet::BitStream& bitStream);

class RPCFunctions
{
private:
	typedef void(*rpcHandler)(RakNet::BitStream& bitStream);
	struct RPCHandler
	{
		unsigned char id;
		rpcHandler callback;
	};

public:
	RPCFunctions();
	virtual RPCFunctions();

	void addHandlers();
	static void addHandler(unsigned char id, rpcHandler callback);
	void processPacket(const RakNet::SystemAddress& socket, RakNet::BitStream& bitStream);

protected:
	DECLARE_RPC(initialDataStream);

	static Player* sourcePlayer;

	std::vector<RPCHandler*> rpcHandlers;

public:
	enum eRPCFunctions
	{
		INITIAL_DATA_STREAM
	};
};
