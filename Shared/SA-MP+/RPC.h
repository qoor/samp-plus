#pragma once

#include <map>
#include <RakNet/BitStream.h>

#define RPC_CALLBACK void
#define RPC_ARGS RakNet::BitStream& bitStream, int extra
#define DECLARE_RPC(a) static RPC_CALLBACK a(RPC_ARGS)

typedef RPC_CALLBACK(*RPCFunction_t)(RPC_ARGS);

enum eRPC : unsigned short
{
	DONT_USE_ZERO = 0,

	SET_GAME_SPEED,
	SET_WAVE_HEIGHT,
	SET_SKY_GRADIENT,
	RESET_SKY_GRADIENT,
	SET_HEAT_HAZE,
	RESET_HEAT_HAZE,
	SET_BLUR_LEVEL,
	SET_FPS_LIMIT,
	SET_CLOUDS_ENABLED,
	SET_AIRCRAFT_MAX_HEIGHT,
	SET_RAIN_LEVEL,
	SET_SUN_SIZE,
	SET_SUN_COLOR,
	SET_WIND_VELOCITY,
	SET_FAR_CLIP_DISTANCE,
	SET_FOG_DISTANCE,
	RESET_RAIN_LEVEL,
	RESET_SUN_SIZE,
	RESET_SUN_COLOR,
	RESET_WIND_VELOCITY,
	RESET_FAR_CLIP_DISTANCE,
	RESET_FOG_DISTANCE,
	SET_MOON_SIZE,
	RESET_MOON_SIZE,

	CREATE_MARKER,
	DESTROY_MARKER,

	END_RPC
};

class RPC
{
private:
	static std::map<unsigned short, RPCFunction_t> handlerFunctions;

	RPC() {}
	~RPC() {}

public:
	static bool addRPCHandler(unsigned short rpcid, RPCFunction_t function);
	static void update(unsigned short rpcid, RakNet::BitStream& bitStreamData, int extra = 0);
};
