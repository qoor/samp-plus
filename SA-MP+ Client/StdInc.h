#pragma once

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#pragma message("Compiling precompiled header.\n")

// Pragmas
#pragma warning (disable:4409)
#pragma warning (disable:4250)

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <RakNet/RakPeerInterface.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/BitStream.h>

#include <DirectX/d3dx9.h>

typedef unsigned char byte;

//#include <WinSock2.h>
//#include <windows.h>
#define MTA_CLIENT
#define SHARED_UTIL_WITH_HASH_MAP
#define SHARED_UTIL_WITH_FAST_HASH_MAP
#include "SharedUtil.h"
#include "SharedUtil.MemAccess.h"
#include <stdio.h>

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

// SDK includes
#include "Core.h"
#include "Settings.h"
#include "Network.h"

/*#include <core/CCoreInterface.h>
#include <net/CNet.h>*/
#include <game/CGame.h>
#include <multiplayer/CMultiplayer.h>
#include <game_sa/gamesa_init.h>
#include <Memory.h>
#include <../version.h>
#include <ijsify.h>
#include <CMatrix_Pad.h>
#include <CVector.h>
#include <CVector4D.h>
#include <CMatrix4.h>
#include <CSphere.h>

#include <SA-MP+/Debug.h>

#include "CSAMP.h"
#include <Client/Enums.h>
#include <Client/Utils.h>
#include <Client/ClientGame.h>
#include <Client/ClientManager.h>
#include <Client/ClientEntity.h>

#include <Client/StaticFunctionDefinations.h>
