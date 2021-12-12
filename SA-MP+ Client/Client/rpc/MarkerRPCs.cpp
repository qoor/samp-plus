#include "StdInc.h"

#include "MarkerRPCs.h"
#include "Client/ClientMarker.h"

void MarkerRPCs::loadFunctions()
{
	RPC::addRPCHandler(CREATE_MARKER, createMarker);
	RPC::addRPCHandler(DESTROY_MARKER, destroyMarker);
}

void MarkerRPCs::createMarker(RPC_ARGS)
{
	Debug::write("付目 积己 夸没 罐澜.");

	bool isLocal;
	int markerid;
	float x, y, z;
	RakNet::RakString type;
	float size;
	int r, g, b, a;

	if (bitStream.Read(isLocal) && bitStream.Read(markerid) &&
		bitStream.Read(x) && bitStream.Read(y) && bitStream.Read(z) &&
		bitStream.Read(type) && bitStream.Read(size) &&
		bitStream.Read(r) && bitStream.Read(g) && bitStream.Read(b) && bitStream.Read(a))
	{
		Debug::write("isLocal = %d, markerid = %d, x = %.4f, y = %.4f, z = %.4f, type = %s, size = %.1f, r = %d, g = %d, b = %d, a = %d",
			isLocal, markerid, x, y, z, type.C_String(), size, r, g, b, a);
		ClientMarker* marker = StaticFunctionDefinations::createMarker(markerid, isLocal, CVector(x, y, z), type.C_String(), size, SColorRGBA(r, g, b, a));

		Debug::write("付目 积己 夸没 凳.");
	}
}

void MarkerRPCs::destroyMarker(RPC_ARGS)
{
	int markerid;

	if (bitStream.Read(markerid))
		StaticFunctionDefinations::destroyMarker(markerid);
}