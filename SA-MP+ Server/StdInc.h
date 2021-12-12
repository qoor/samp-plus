// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#define INVALID_PLAYER_ID (0xFFFF)

#include "targetver.h"

#ifdef WIN32
#pragma message("Compiling precompiled header.\n")
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#endif

#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "SharedUtil.h"
#include "CVector.h"
#include "CVector4D.h"
#include "CSphere.h"
#include "CBox.h"
#include "CMatrix.h"

#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/RakString.h>
#include <RakNet/BitStream.h>

#include "version.h"

#include <SA-MP+/Debug.h>
#include <SA-MP+/PacketType.h>
#include <SA-MP+/RPC.h>

#include <sampgdk/core.h>
#include <sampgdk/sdk.h>
#include <sampgdk/a_players.h>

#include "Settings.h"
#include "Network.h"

#include "packets/Packet.h"
#include "packets/PlayerJoinDataPacket.h"

#include "RPCFunctions.h"
#include "Game.h"
#include "Ped.h"
#include "PedManager.h"
#include "Player.h"
#include "PlayerManager.h"
#include "PacketTranslator.h"

#include "Server.h"

extern Network* g_pNetwork;
extern Game* g_pGame;
