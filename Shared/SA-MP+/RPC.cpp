#include "StdInc.h"

#include "RPC.h"

std::map<unsigned short, RPCFunction_t> RPC::handlerFunctions;

bool RPC::addRPCHandler(unsigned short rpcid, RPCFunction_t function)
{
	if (rpcid > eRPC::END_RPC || function == NULL)
		return false;

	return (handlerFunctions.insert(std::map<unsigned short, RPCFunction_t>::value_type(rpcid, function)).second);
}

void RPC::update(unsigned short rpcid, RakNet::BitStream& bitStreamData, int extra)
{
	std::map<unsigned short, RPCFunction_t>::iterator it = handlerFunctions.find(rpcid);

	if (it != handlerFunctions.end())
		return it->second(bitStreamData, extra);
}
