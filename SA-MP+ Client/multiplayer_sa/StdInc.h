#pragma message("Compiling precompiled header.\n")

#define TIMING_CHECKPOINT(result) Debug::write("%s", result);

// Pragmas
#pragma warning (disable:4250)
#pragma warning (disable:4006)

#include <WinSock2.h>
#include <windows.h>
//#define MTA_CLIENT
#define SHARED_UTIL_WITH_HASH_MAP
#define SHARED_UTIL_WITH_FAST_HASH_MAP
#define SHARED_UTIL_WITH_SYS_INFO
#include "SharedUtil.h"
#include "SharedUtil.MemAccess.h"
#include <stdio.h>

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

// SDK includes
/*#include <core/CCoreInterface.h>
#include <net/CNet.h>*/
#include "Core.h"
#include "Network.h"
#include <game/CGame.h>
#include <CMatrix_Pad.h>
#include <../version.h>

// Multiplayer includes
#include "multiplayersa_init.h"
#include "multiplayer_keysync.h"
#include "multiplayer_hooksystem.h"
#include "multiplayer_shotsync.h"
#include "CMultiplayerSA.h"
#include "COffsetsMP.h"
#include "CRemoteDataSA.h"

extern CMultiplayerSA* pMultiplayer;
