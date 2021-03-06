#ifndef SAMPGDK_A_PLAYERS_H
#define SAMPGDK_A_PLAYERS_H

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/types.h>

#define SPECIAL_ACTION_NONE (0)
#define SPECIAL_ACTION_DUCK (1)
#define SPECIAL_ACTION_USEJETPACK (2)
#define SPECIAL_ACTION_ENTER_VEHICLE (3)
#define SPECIAL_ACTION_EXIT_VEHICLE (4)
#define SPECIAL_ACTION_DANCE1 (5)
#define SPECIAL_ACTION_DANCE2 (6)
#define SPECIAL_ACTION_DANCE3 (7)
#define SPECIAL_ACTION_DANCE4 (8)
#define SPECIAL_ACTION_HANDSUP (10)
#define SPECIAL_ACTION_USECELLPHONE (11)
#define SPECIAL_ACTION_SITTING (12)
#define SPECIAL_ACTION_STOPUSECELLPHONE (13)
#define SPECIAL_ACTION_DRINK_BEER (20)
#define SPECIAL_ACTION_SMOKE_CIGGY (21)
#define SPECIAL_ACTION_DRINK_WINE (22)
#define SPECIAL_ACTION_DRINK_SPRUNK (23)
#define SPECIAL_ACTION_CUFFED (24)
#define SPECIAL_ACTION_CARRY (25)
#define SPECIAL_ACTION_PISSING (68)
#define FIGHT_STYLE_NORMAL (4)
#define FIGHT_STYLE_BOXING (5)
#define FIGHT_STYLE_KUNGFU (6)
#define FIGHT_STYLE_KNEEHEAD (7)
#define FIGHT_STYLE_GRABKICK (15)
#define FIGHT_STYLE_ELBOW (16)
#define WEAPONSKILL_PISTOL (0)
#define WEAPONSKILL_PISTOL_SILENCED (1)
#define WEAPONSKILL_DESERT_EAGLE (2)
#define WEAPONSKILL_SHOTGUN (3)
#define WEAPONSKILL_SAWNOFF_SHOTGUN (4)
#define WEAPONSKILL_SPAS12_SHOTGUN (5)
#define WEAPONSKILL_MICRO_UZI (6)
#define WEAPONSKILL_MP5 (7)
#define WEAPONSKILL_AK47 (8)
#define WEAPONSKILL_M4 (9)
#define WEAPONSKILL_SNIPERRIFLE (10)
#define WEAPONSTATE_UNKNOWN (-1)
#define WEAPONSTATE_NO_BULLETS (0)
#define WEAPONSTATE_LAST_BULLET (1)
#define WEAPONSTATE_MORE_BULLETS (2)
#define WEAPONSTATE_RELOADING (3)
#define MAX_PLAYER_ATTACHED_OBJECTS (10)
#define PLAYER_VARTYPE_NONE (0)
#define PLAYER_VARTYPE_INT (1)
#define PLAYER_VARTYPE_STRING (2)
#define PLAYER_VARTYPE_FLOAT (3)
#define MAX_CHATBUBBLE_LENGTH (144)
#define MAPICON_LOCAL (0)
#define MAPICON_GLOBAL (1)
#define MAPICON_LOCAL_CHECKPOINT (2)
#define MAPICON_GLOBAL_CHECKPOINT (3)
#define CAMERA_CUT (2)
#define CAMERA_MOVE (1)
#define SPECTATE_MODE_NORMAL (1)
#define SPECTATE_MODE_FIXED (2)
#define SPECTATE_MODE_SIDE (3)
#define PLAYER_RECORDING_TYPE_NONE (0)
#define PLAYER_RECORDING_TYPE_DRIVER (1)
#define PLAYER_RECORDING_TYPE_ONFOOT (2)

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetSpawnInfo">SetSpawnInfo on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SpawnPlayer">SpawnPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SpawnPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerPos">SetPlayerPos on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerPos(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerPosFindZ">SetPlayerPosFindZ on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerPosFindZ(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerPos">GetPlayerPos on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerPos(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerFacingAngle">SetPlayerFacingAngle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerFacingAngle(int playerid, float angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerFacingAngle">GetPlayerFacingAngle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerFacingAngle(int playerid, float * angle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInRangeOfPoint">IsPlayerInRangeOfPoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerDistanceFromPoint">GetPlayerDistanceFromPoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(float, GetPlayerDistanceFromPoint(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerStreamedIn">IsPlayerStreamedIn on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerStreamedIn(int playerid, int forplayerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerInterior">SetPlayerInterior on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerInterior(int playerid, int interiorid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerInterior">GetPlayerInterior on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerInterior(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerHealth">SetPlayerHealth on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerHealth(int playerid, float health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerHealth">GetPlayerHealth on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerHealth(int playerid, float * health));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerArmour">SetPlayerArmour on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerArmour(int playerid, float armour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerArmour">GetPlayerArmour on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerArmour(int playerid, float * armour));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerAmmo">SetPlayerAmmo on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerAmmo(int playerid, int weaponid, int ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerAmmo">GetPlayerAmmo on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerAmmo(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeaponState">GetPlayerWeaponState on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerWeaponState(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTargetPlayer">GetPlayerTargetPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerTargetPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTargetActor">GetPlayerTargetActor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerTargetActor(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerTeam">SetPlayerTeam on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerTeam(int playerid, int teamid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTeam">GetPlayerTeam on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerTeam(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerScore">SetPlayerScore on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerScore(int playerid, int score));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerScore">GetPlayerScore on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerScore(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerDrunkLevel">GetPlayerDrunkLevel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerDrunkLevel(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerDrunkLevel">SetPlayerDrunkLevel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerDrunkLevel(int playerid, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerColor">SetPlayerColor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerColor(int playerid, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerColor">GetPlayerColor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerColor(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSkin">SetPlayerSkin on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerSkin(int playerid, int skinid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSkin">GetPlayerSkin on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerSkin(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GivePlayerWeapon">GivePlayerWeapon on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GivePlayerWeapon(int playerid, int weaponid, int ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ResetPlayerWeapons">ResetPlayerWeapons on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ResetPlayerWeapons(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerArmedWeapon">SetPlayerArmedWeapon on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerArmedWeapon(int playerid, int weaponid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeaponData">GetPlayerWeaponData on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GivePlayerMoney">GivePlayerMoney on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GivePlayerMoney(int playerid, int money));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ResetPlayerMoney">ResetPlayerMoney on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ResetPlayerMoney(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerName">SetPlayerName on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, SetPlayerName(int playerid, const char * name));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerMoney">GetPlayerMoney on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerMoney(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerState">GetPlayerState on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerState(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerIp">GetPlayerIp on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerIp(int playerid, char * ip, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerPing">GetPlayerPing on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerPing(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWeapon">GetPlayerWeapon on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerWeapon(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerKeys">GetPlayerKeys on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerKeys(int playerid, int * keys, int * updown, int * leftright));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerName">GetPlayerName on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerName(int playerid, char * name, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerTime">SetPlayerTime on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerTime(int playerid, int hour, int minute));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerTime">GetPlayerTime on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerTime(int playerid, int * hour, int * minute));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerClock">TogglePlayerClock on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, TogglePlayerClock(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWeather">SetPlayerWeather on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerWeather(int playerid, int weather));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ForceClassSelection">ForceClassSelection on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ForceClassSelection(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWantedLevel">SetPlayerWantedLevel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerWantedLevel(int playerid, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerWantedLevel">GetPlayerWantedLevel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerWantedLevel(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerFightingStyle">SetPlayerFightingStyle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerFightingStyle(int playerid, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerFightingStyle">GetPlayerFightingStyle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerFightingStyle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerVelocity">SetPlayerVelocity on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerVelocity(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVelocity">GetPlayerVelocity on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerVelocity(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayCrimeReportForPlayer">PlayCrimeReportForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayCrimeReportForPlayer(int playerid, int suspectid, int crime));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayAudioStreamForPlayer">PlayAudioStreamForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayAudioStreamForPlayer(int playerid, const char * url, float posX, float posY, float posZ, float distance, bool usepos));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopAudioStreamForPlayer">StopAudioStreamForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, StopAudioStreamForPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerShopName">SetPlayerShopName on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerShopName(int playerid, const char * shopname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSkillLevel">SetPlayerSkillLevel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerSkillLevel(int playerid, int skill, int level));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSurfingVehicleID">GetPlayerSurfingVehicleID on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerSurfingVehicleID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSurfingObjectID">GetPlayerSurfingObjectID on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerSurfingObjectID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemoveBuildingForPlayer">RemoveBuildingForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerLastShotVectors">GetPlayerLastShotVectors on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerLastShotVectors(int playerid, float * fOriginX, float * fOriginY, float * fOriginZ, float * fHitPosX, float * fHitPosY, float * fHitPosZ));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerAttachedObject">SetPlayerAttachedObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerAttachedObject">RemovePlayerAttachedObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, RemovePlayerAttachedObject(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerAttachedObjectSlotUsed">IsPlayerAttachedObjectSlotUsed on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerAttachedObjectSlotUsed(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EditAttachedObject">EditAttachedObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, EditAttachedObject(int playerid, int index));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreatePlayerTextDraw">CreatePlayerTextDraw on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, CreatePlayerTextDraw(int playerid, float x, float y, const char * text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawDestroy">PlayerTextDrawDestroy on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawDestroy(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawLetterSize">PlayerTextDrawLetterSize on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawLetterSize(int playerid, int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawTextSize">PlayerTextDrawTextSize on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawTextSize(int playerid, int text, float x, float y));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawAlignment">PlayerTextDrawAlignment on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawAlignment(int playerid, int text, int alignment));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawColor">PlayerTextDrawColor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawUseBox">PlayerTextDrawUseBox on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawUseBox(int playerid, int text, bool use));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawBoxColor">PlayerTextDrawBoxColor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawBoxColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetShadow">PlayerTextDrawSetShadow on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetShadow(int playerid, int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetOutline">PlayerTextDrawSetOutline on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetOutline(int playerid, int text, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawBackgroundColor">PlayerTextDrawBackgroundColor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawBackgroundColor(int playerid, int text, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawFont">PlayerTextDrawFont on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawFont(int playerid, int text, int font));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetProportional">PlayerTextDrawSetProportional on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetProportional(int playerid, int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetSelectable">PlayerTextDrawSetSelectable on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetSelectable(int playerid, int text, bool set));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawShow">PlayerTextDrawShow on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawShow(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawHide">PlayerTextDrawHide on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawHide(int playerid, int text));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetString">PlayerTextDrawSetString on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetString(int playerid, int text, const char * string));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewModel">PlayerTextDrawSetPreviewModel on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewModel(int playerid, int text, int modelindex));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewRot">PlayerTextDrawSetPreviewRot on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewRot(int playerid, int text, float fRotX, float fRotY, float fRotZ, float fZoom));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawSetPreviewVehCol">PlayerTextDrawSetPreviewVehCol on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerTextDrawSetPreviewVehCol(int playerid, int text, int color1, int color2));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarInt">SetPVarInt on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPVarInt(int playerid, const char * varname, int value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarInt">GetPVarInt on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPVarInt(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarString">SetPVarString on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPVarString(int playerid, const char * varname, const char * value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarString">GetPVarString on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPVarString(int playerid, const char * varname, char * value, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPVarFloat">SetPVarFloat on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPVarFloat(int playerid, const char * varname, float value));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarFloat">GetPVarFloat on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(float, GetPVarFloat(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DeletePVar">DeletePVar on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, DeletePVar(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarsUpperIndex">GetPVarsUpperIndex on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPVarsUpperIndex(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarNameAtIndex">GetPVarNameAtIndex on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPVarNameAtIndex(int playerid, int index, char * varname, int size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPVarType">GetPVarType on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPVarType(int playerid, const char * varname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerChatBubble">SetPlayerChatBubble on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerChatBubble(int playerid, const char * text, int color, float drawdistance, int expiretime));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PutPlayerInVehicle">PutPlayerInVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PutPlayerInVehicle(int playerid, int vehicleid, int seatid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVehicleID">GetPlayerVehicleID on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerVehicleID(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVehicleSeat">GetPlayerVehicleSeat on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerVehicleSeat(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerFromVehicle">RemovePlayerFromVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, RemovePlayerFromVehicle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerControllable">TogglePlayerControllable on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, TogglePlayerControllable(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerPlaySound">PlayerPlaySound on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerPlaySound(int playerid, int soundid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ApplyAnimation">ApplyAnimation on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ClearAnimations">ClearAnimations on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ClearAnimations(int playerid, bool forcesync));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerAnimationIndex">GetPlayerAnimationIndex on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerAnimationIndex(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetAnimationName">GetAnimationName on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetAnimationName(int index, char * animlib, int animlib_size, char * animname, int animname_size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerSpecialAction">GetPlayerSpecialAction on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerSpecialAction(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerSpecialAction">SetPlayerSpecialAction on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerSpecialAction(int playerid, int actionid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisableRemoteVehicleCollisions">DisableRemoteVehicleCollisions on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, DisableRemoteVehicleCollisions(int playerid, bool disable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCheckpoint">SetPlayerCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerCheckpoint(int playerid, float x, float y, float z, float size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisablePlayerCheckpoint">DisablePlayerCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, DisablePlayerCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerRaceCheckpoint">SetPlayerRaceCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/DisablePlayerRaceCheckpoint">DisablePlayerRaceCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, DisablePlayerRaceCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerWorldBounds">SetPlayerWorldBounds on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerMarkerForPlayer">SetPlayerMarkerForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/ShowPlayerNameTagForPlayer">ShowPlayerNameTagForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerMapIcon">SetPlayerMapIcon on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/RemovePlayerMapIcon">RemovePlayerMapIcon on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, RemovePlayerMapIcon(int playerid, int iconid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AllowPlayerTeleport">AllowPlayerTeleport on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, AllowPlayerTeleport(int playerid, bool allow));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCameraPos">SetPlayerCameraPos on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerCameraPos(int playerid, float x, float y, float z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerCameraLookAt">SetPlayerCameraLookAt on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetCameraBehindPlayer">SetCameraBehindPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetCameraBehindPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraPos">GetPlayerCameraPos on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerCameraPos(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraFrontVector">GetPlayerCameraFrontVector on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraMode">GetPlayerCameraMode on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerCameraMode(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnablePlayerCameraTarget">EnablePlayerCameraTarget on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, EnablePlayerCameraTarget(int playerid, bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraTargetObject">GetPlayerCameraTargetObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerCameraTargetObject(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraTargetVehicle">GetPlayerCameraTargetVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerCameraTargetVehicle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraTargetPlayer">GetPlayerCameraTargetPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerCameraTargetPlayer(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraTargetActor">GetPlayerCameraTargetActor on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerCameraTargetActor(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraAspectRatio">GetPlayerCameraAspectRatio on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(float, GetPlayerCameraAspectRatio(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerCameraZoom">GetPlayerCameraZoom on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(float, GetPlayerCameraZoom(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachCameraToObject">AttachCameraToObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, AttachCameraToObject(int playerid, int objectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/AttachCameraToPlayerObject">AttachCameraToPlayerObject on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, AttachCameraToPlayerObject(int playerid, int playerobjectid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/InterpolateCameraPos">InterpolateCameraPos on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/InterpolateCameraLookAt">InterpolateCameraLookAt on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerConnected">IsPlayerConnected on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerConnected(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInVehicle">IsPlayerInVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerInVehicle(int playerid, int vehicleid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInAnyVehicle">IsPlayerInAnyVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerInAnyVehicle(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInCheckpoint">IsPlayerInCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerInCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/IsPlayerInRaceCheckpoint">IsPlayerInRaceCheckpoint on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, IsPlayerInRaceCheckpoint(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/SetPlayerVirtualWorld">SetPlayerVirtualWorld on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, SetPlayerVirtualWorld(int playerid, int worldid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/GetPlayerVirtualWorld">GetPlayerVirtualWorld on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(int, GetPlayerVirtualWorld(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableStuntBonusForPlayer">EnableStuntBonusForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, EnableStuntBonusForPlayer(int playerid, bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/EnableStuntBonusForAll">EnableStuntBonusForAll on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, EnableStuntBonusForAll(bool enable));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/TogglePlayerSpectating">TogglePlayerSpectating on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, TogglePlayerSpectating(int playerid, bool toggle));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerSpectatePlayer">PlayerSpectatePlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerSpectatePlayer(int playerid, int targetplayerid, int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/PlayerSpectateVehicle">PlayerSpectateVehicle on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StartRecordingPlayerData">StartRecordingPlayerData on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, StartRecordingPlayerData(int playerid, int recordtype, const char * recordname));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/StopRecordingPlayerData">StopRecordingPlayerData on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, StopRecordingPlayerData(int playerid));

/**
 * \ingroup natives
 * \see <a href="http://wiki.sa-mp.com/wiki/CreateExplosionForPlayer">CreateExplosionForPlayer on SA-MP Wiki</a>
 */
SAMPGDK_NATIVE(bool, CreateExplosionForPlayer(int playerid, float X, float Y, float Z, int type, float Radius));

#ifndef DOXYGEN

#if defined SAMPGDK_CPP_WRAPPERS && !defined IN_SAMPGDK

namespace sampgdk {

inline bool SetSpawnInfo(int playerid, int team, int skin, float x, float y, float z, float rotation, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo) {
  return sampgdk_SetSpawnInfo(playerid, team, skin, x, y, z, rotation, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
}

inline bool SpawnPlayer(int playerid) {
  return sampgdk_SpawnPlayer(playerid);
}

inline bool SetPlayerPos(int playerid, float x, float y, float z) {
  return sampgdk_SetPlayerPos(playerid, x, y, z);
}

inline bool SetPlayerPosFindZ(int playerid, float x, float y, float z) {
  return sampgdk_SetPlayerPosFindZ(playerid, x, y, z);
}

inline bool GetPlayerPos(int playerid, float * x, float * y, float * z) {
  return sampgdk_GetPlayerPos(playerid, x, y, z);
}

inline bool SetPlayerFacingAngle(int playerid, float angle) {
  return sampgdk_SetPlayerFacingAngle(playerid, angle);
}

inline bool GetPlayerFacingAngle(int playerid, float * angle) {
  return sampgdk_GetPlayerFacingAngle(playerid, angle);
}

inline bool IsPlayerInRangeOfPoint(int playerid, float range, float x, float y, float z) {
  return sampgdk_IsPlayerInRangeOfPoint(playerid, range, x, y, z);
}

inline float GetPlayerDistanceFromPoint(int playerid, float x, float y, float z) {
  return sampgdk_GetPlayerDistanceFromPoint(playerid, x, y, z);
}

inline bool IsPlayerStreamedIn(int playerid, int forplayerid) {
  return sampgdk_IsPlayerStreamedIn(playerid, forplayerid);
}

inline bool SetPlayerInterior(int playerid, int interiorid) {
  return sampgdk_SetPlayerInterior(playerid, interiorid);
}

inline int GetPlayerInterior(int playerid) {
  return sampgdk_GetPlayerInterior(playerid);
}

inline bool SetPlayerHealth(int playerid, float health) {
  return sampgdk_SetPlayerHealth(playerid, health);
}

inline bool GetPlayerHealth(int playerid, float * health) {
  return sampgdk_GetPlayerHealth(playerid, health);
}

inline bool SetPlayerArmour(int playerid, float armour) {
  return sampgdk_SetPlayerArmour(playerid, armour);
}

inline bool GetPlayerArmour(int playerid, float * armour) {
  return sampgdk_GetPlayerArmour(playerid, armour);
}

inline bool SetPlayerAmmo(int playerid, int weaponid, int ammo) {
  return sampgdk_SetPlayerAmmo(playerid, weaponid, ammo);
}

inline int GetPlayerAmmo(int playerid) {
  return sampgdk_GetPlayerAmmo(playerid);
}

inline int GetPlayerWeaponState(int playerid) {
  return sampgdk_GetPlayerWeaponState(playerid);
}

inline int GetPlayerTargetPlayer(int playerid) {
  return sampgdk_GetPlayerTargetPlayer(playerid);
}

inline int GetPlayerTargetActor(int playerid) {
  return sampgdk_GetPlayerTargetActor(playerid);
}

inline bool SetPlayerTeam(int playerid, int teamid) {
  return sampgdk_SetPlayerTeam(playerid, teamid);
}

inline int GetPlayerTeam(int playerid) {
  return sampgdk_GetPlayerTeam(playerid);
}

inline bool SetPlayerScore(int playerid, int score) {
  return sampgdk_SetPlayerScore(playerid, score);
}

inline int GetPlayerScore(int playerid) {
  return sampgdk_GetPlayerScore(playerid);
}

inline int GetPlayerDrunkLevel(int playerid) {
  return sampgdk_GetPlayerDrunkLevel(playerid);
}

inline bool SetPlayerDrunkLevel(int playerid, int level) {
  return sampgdk_SetPlayerDrunkLevel(playerid, level);
}

inline bool SetPlayerColor(int playerid, int color) {
  return sampgdk_SetPlayerColor(playerid, color);
}

inline int GetPlayerColor(int playerid) {
  return sampgdk_GetPlayerColor(playerid);
}

inline bool SetPlayerSkin(int playerid, int skinid) {
  return sampgdk_SetPlayerSkin(playerid, skinid);
}

inline int GetPlayerSkin(int playerid) {
  return sampgdk_GetPlayerSkin(playerid);
}

inline bool GivePlayerWeapon(int playerid, int weaponid, int ammo) {
  return sampgdk_GivePlayerWeapon(playerid, weaponid, ammo);
}

inline bool ResetPlayerWeapons(int playerid) {
  return sampgdk_ResetPlayerWeapons(playerid);
}

inline bool SetPlayerArmedWeapon(int playerid, int weaponid) {
  return sampgdk_SetPlayerArmedWeapon(playerid, weaponid);
}

inline bool GetPlayerWeaponData(int playerid, int slot, int * weapon, int * ammo) {
  return sampgdk_GetPlayerWeaponData(playerid, slot, weapon, ammo);
}

inline bool GivePlayerMoney(int playerid, int money) {
  return sampgdk_GivePlayerMoney(playerid, money);
}

inline bool ResetPlayerMoney(int playerid) {
  return sampgdk_ResetPlayerMoney(playerid);
}

inline int SetPlayerName(int playerid, const char * name) {
  return sampgdk_SetPlayerName(playerid, name);
}

inline int GetPlayerMoney(int playerid) {
  return sampgdk_GetPlayerMoney(playerid);
}

inline int GetPlayerState(int playerid) {
  return sampgdk_GetPlayerState(playerid);
}

inline bool GetPlayerIp(int playerid, char * ip, int size) {
  return sampgdk_GetPlayerIp(playerid, ip, size);
}

inline int GetPlayerPing(int playerid) {
  return sampgdk_GetPlayerPing(playerid);
}

inline int GetPlayerWeapon(int playerid) {
  return sampgdk_GetPlayerWeapon(playerid);
}

inline bool GetPlayerKeys(int playerid, int * keys, int * updown, int * leftright) {
  return sampgdk_GetPlayerKeys(playerid, keys, updown, leftright);
}

inline int GetPlayerName(int playerid, char * name, int size) {
  return sampgdk_GetPlayerName(playerid, name, size);
}

inline bool SetPlayerTime(int playerid, int hour, int minute) {
  return sampgdk_SetPlayerTime(playerid, hour, minute);
}

inline bool GetPlayerTime(int playerid, int * hour, int * minute) {
  return sampgdk_GetPlayerTime(playerid, hour, minute);
}

inline bool TogglePlayerClock(int playerid, bool toggle) {
  return sampgdk_TogglePlayerClock(playerid, toggle);
}

inline bool SetPlayerWeather(int playerid, int weather) {
  return sampgdk_SetPlayerWeather(playerid, weather);
}

inline bool ForceClassSelection(int playerid) {
  return sampgdk_ForceClassSelection(playerid);
}

inline bool SetPlayerWantedLevel(int playerid, int level) {
  return sampgdk_SetPlayerWantedLevel(playerid, level);
}

inline int GetPlayerWantedLevel(int playerid) {
  return sampgdk_GetPlayerWantedLevel(playerid);
}

inline bool SetPlayerFightingStyle(int playerid, int style) {
  return sampgdk_SetPlayerFightingStyle(playerid, style);
}

inline int GetPlayerFightingStyle(int playerid) {
  return sampgdk_GetPlayerFightingStyle(playerid);
}

inline bool SetPlayerVelocity(int playerid, float x, float y, float z) {
  return sampgdk_SetPlayerVelocity(playerid, x, y, z);
}

inline bool GetPlayerVelocity(int playerid, float * x, float * y, float * z) {
  return sampgdk_GetPlayerVelocity(playerid, x, y, z);
}

inline bool PlayCrimeReportForPlayer(int playerid, int suspectid, int crime) {
  return sampgdk_PlayCrimeReportForPlayer(playerid, suspectid, crime);
}

inline bool PlayAudioStreamForPlayer(int playerid, const char * url, float posX = 0.0, float posY = 0.0, float posZ = 0.0, float distance = 50.0, bool usepos = false) {
  return sampgdk_PlayAudioStreamForPlayer(playerid, url, posX, posY, posZ, distance, usepos);
}

inline bool StopAudioStreamForPlayer(int playerid) {
  return sampgdk_StopAudioStreamForPlayer(playerid);
}

inline bool SetPlayerShopName(int playerid, const char * shopname) {
  return sampgdk_SetPlayerShopName(playerid, shopname);
}

inline bool SetPlayerSkillLevel(int playerid, int skill, int level) {
  return sampgdk_SetPlayerSkillLevel(playerid, skill, level);
}

inline int GetPlayerSurfingVehicleID(int playerid) {
  return sampgdk_GetPlayerSurfingVehicleID(playerid);
}

inline int GetPlayerSurfingObjectID(int playerid) {
  return sampgdk_GetPlayerSurfingObjectID(playerid);
}

inline bool RemoveBuildingForPlayer(int playerid, int modelid, float fX, float fY, float fZ, float fRadius) {
  return sampgdk_RemoveBuildingForPlayer(playerid, modelid, fX, fY, fZ, fRadius);
}

inline bool GetPlayerLastShotVectors(int playerid, float * fOriginX, float * fOriginY, float * fOriginZ, float * fHitPosX, float * fHitPosY, float * fHitPosZ) {
  return sampgdk_GetPlayerLastShotVectors(playerid, fOriginX, fOriginY, fOriginZ, fHitPosX, fHitPosY, fHitPosZ);
}

inline bool SetPlayerAttachedObject(int playerid, int index, int modelid, int bone, float fOffsetX = 0.0, float fOffsetY = 0.0, float fOffsetZ = 0.0, float fRotX = 0.0, float fRotY = 0.0, float fRotZ = 0.0, float fScaleX = 1.0, float fScaleY = 1.0, float fScaleZ = 1.0, int materialcolor1 = 0, int materialcolor2 = 0) {
  return sampgdk_SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
}

inline bool RemovePlayerAttachedObject(int playerid, int index) {
  return sampgdk_RemovePlayerAttachedObject(playerid, index);
}

inline bool IsPlayerAttachedObjectSlotUsed(int playerid, int index) {
  return sampgdk_IsPlayerAttachedObjectSlotUsed(playerid, index);
}

inline bool EditAttachedObject(int playerid, int index) {
  return sampgdk_EditAttachedObject(playerid, index);
}

inline int CreatePlayerTextDraw(int playerid, float x, float y, const char * text) {
  return sampgdk_CreatePlayerTextDraw(playerid, x, y, text);
}

inline bool PlayerTextDrawDestroy(int playerid, int text) {
  return sampgdk_PlayerTextDrawDestroy(playerid, text);
}

inline bool PlayerTextDrawLetterSize(int playerid, int text, float x, float y) {
  return sampgdk_PlayerTextDrawLetterSize(playerid, text, x, y);
}

inline bool PlayerTextDrawTextSize(int playerid, int text, float x, float y) {
  return sampgdk_PlayerTextDrawTextSize(playerid, text, x, y);
}

inline bool PlayerTextDrawAlignment(int playerid, int text, int alignment) {
  return sampgdk_PlayerTextDrawAlignment(playerid, text, alignment);
}

inline bool PlayerTextDrawColor(int playerid, int text, int color) {
  return sampgdk_PlayerTextDrawColor(playerid, text, color);
}

inline bool PlayerTextDrawUseBox(int playerid, int text, bool use) {
  return sampgdk_PlayerTextDrawUseBox(playerid, text, use);
}

inline bool PlayerTextDrawBoxColor(int playerid, int text, int color) {
  return sampgdk_PlayerTextDrawBoxColor(playerid, text, color);
}

inline bool PlayerTextDrawSetShadow(int playerid, int text, int size) {
  return sampgdk_PlayerTextDrawSetShadow(playerid, text, size);
}

inline bool PlayerTextDrawSetOutline(int playerid, int text, int size) {
  return sampgdk_PlayerTextDrawSetOutline(playerid, text, size);
}

inline bool PlayerTextDrawBackgroundColor(int playerid, int text, int color) {
  return sampgdk_PlayerTextDrawBackgroundColor(playerid, text, color);
}

inline bool PlayerTextDrawFont(int playerid, int text, int font) {
  return sampgdk_PlayerTextDrawFont(playerid, text, font);
}

inline bool PlayerTextDrawSetProportional(int playerid, int text, bool set) {
  return sampgdk_PlayerTextDrawSetProportional(playerid, text, set);
}

inline bool PlayerTextDrawSetSelectable(int playerid, int text, bool set) {
  return sampgdk_PlayerTextDrawSetSelectable(playerid, text, set);
}

inline bool PlayerTextDrawShow(int playerid, int text) {
  return sampgdk_PlayerTextDrawShow(playerid, text);
}

inline bool PlayerTextDrawHide(int playerid, int text) {
  return sampgdk_PlayerTextDrawHide(playerid, text);
}

inline bool PlayerTextDrawSetString(int playerid, int text, const char * string) {
  return sampgdk_PlayerTextDrawSetString(playerid, text, string);
}

inline bool PlayerTextDrawSetPreviewModel(int playerid, int text, int modelindex) {
  return sampgdk_PlayerTextDrawSetPreviewModel(playerid, text, modelindex);
}

inline bool PlayerTextDrawSetPreviewRot(int playerid, int text, float fRotX, float fRotY, float fRotZ, float fZoom = 1.0) {
  return sampgdk_PlayerTextDrawSetPreviewRot(playerid, text, fRotX, fRotY, fRotZ, fZoom);
}

inline bool PlayerTextDrawSetPreviewVehCol(int playerid, int text, int color1, int color2) {
  return sampgdk_PlayerTextDrawSetPreviewVehCol(playerid, text, color1, color2);
}

inline bool SetPVarInt(int playerid, const char * varname, int value) {
  return sampgdk_SetPVarInt(playerid, varname, value);
}

inline int GetPVarInt(int playerid, const char * varname) {
  return sampgdk_GetPVarInt(playerid, varname);
}

inline bool SetPVarString(int playerid, const char * varname, const char * value) {
  return sampgdk_SetPVarString(playerid, varname, value);
}

inline bool GetPVarString(int playerid, const char * varname, char * value, int size) {
  return sampgdk_GetPVarString(playerid, varname, value, size);
}

inline bool SetPVarFloat(int playerid, const char * varname, float value) {
  return sampgdk_SetPVarFloat(playerid, varname, value);
}

inline float GetPVarFloat(int playerid, const char * varname) {
  return sampgdk_GetPVarFloat(playerid, varname);
}

inline bool DeletePVar(int playerid, const char * varname) {
  return sampgdk_DeletePVar(playerid, varname);
}

inline int GetPVarsUpperIndex(int playerid) {
  return sampgdk_GetPVarsUpperIndex(playerid);
}

inline bool GetPVarNameAtIndex(int playerid, int index, char * varname, int size) {
  return sampgdk_GetPVarNameAtIndex(playerid, index, varname, size);
}

inline int GetPVarType(int playerid, const char * varname) {
  return sampgdk_GetPVarType(playerid, varname);
}

inline bool SetPlayerChatBubble(int playerid, const char * text, int color, float drawdistance, int expiretime) {
  return sampgdk_SetPlayerChatBubble(playerid, text, color, drawdistance, expiretime);
}

inline bool PutPlayerInVehicle(int playerid, int vehicleid, int seatid) {
  return sampgdk_PutPlayerInVehicle(playerid, vehicleid, seatid);
}

inline int GetPlayerVehicleID(int playerid) {
  return sampgdk_GetPlayerVehicleID(playerid);
}

inline int GetPlayerVehicleSeat(int playerid) {
  return sampgdk_GetPlayerVehicleSeat(playerid);
}

inline bool RemovePlayerFromVehicle(int playerid) {
  return sampgdk_RemovePlayerFromVehicle(playerid);
}

inline bool TogglePlayerControllable(int playerid, bool toggle) {
  return sampgdk_TogglePlayerControllable(playerid, toggle);
}

inline bool PlayerPlaySound(int playerid, int soundid, float x, float y, float z) {
  return sampgdk_PlayerPlaySound(playerid, soundid, x, y, z);
}

inline bool ApplyAnimation(int playerid, const char * animlib, const char * animname, float fDelta, bool loop, bool lockx, bool locky, bool freeze, int time, bool forcesync = false) {
  return sampgdk_ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
}

inline bool ClearAnimations(int playerid, bool forcesync = false) {
  return sampgdk_ClearAnimations(playerid, forcesync);
}

inline int GetPlayerAnimationIndex(int playerid) {
  return sampgdk_GetPlayerAnimationIndex(playerid);
}

inline bool GetAnimationName(int index, char * animlib, int animlib_size, char * animname, int animname_size) {
  return sampgdk_GetAnimationName(index, animlib, animlib_size, animname, animname_size);
}

inline int GetPlayerSpecialAction(int playerid) {
  return sampgdk_GetPlayerSpecialAction(playerid);
}

inline bool SetPlayerSpecialAction(int playerid, int actionid) {
  return sampgdk_SetPlayerSpecialAction(playerid, actionid);
}

inline bool DisableRemoteVehicleCollisions(int playerid, bool disable) {
  return sampgdk_DisableRemoteVehicleCollisions(playerid, disable);
}

inline bool SetPlayerCheckpoint(int playerid, float x, float y, float z, float size) {
  return sampgdk_SetPlayerCheckpoint(playerid, x, y, z, size);
}

inline bool DisablePlayerCheckpoint(int playerid) {
  return sampgdk_DisablePlayerCheckpoint(playerid);
}

inline bool SetPlayerRaceCheckpoint(int playerid, int type, float x, float y, float z, float nextx, float nexty, float nextz, float size) {
  return sampgdk_SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
}

inline bool DisablePlayerRaceCheckpoint(int playerid) {
  return sampgdk_DisablePlayerRaceCheckpoint(playerid);
}

inline bool SetPlayerWorldBounds(int playerid, float x_max, float x_min, float y_max, float y_min) {
  return sampgdk_SetPlayerWorldBounds(playerid, x_max, x_min, y_max, y_min);
}

inline bool SetPlayerMarkerForPlayer(int playerid, int showplayerid, int color) {
  return sampgdk_SetPlayerMarkerForPlayer(playerid, showplayerid, color);
}

inline bool ShowPlayerNameTagForPlayer(int playerid, int showplayerid, bool show) {
  return sampgdk_ShowPlayerNameTagForPlayer(playerid, showplayerid, show);
}

inline bool SetPlayerMapIcon(int playerid, int iconid, float x, float y, float z, int markertype, int color, int style = MAPICON_LOCAL) {
  return sampgdk_SetPlayerMapIcon(playerid, iconid, x, y, z, markertype, color, style);
}

inline bool RemovePlayerMapIcon(int playerid, int iconid) {
  return sampgdk_RemovePlayerMapIcon(playerid, iconid);
}

inline bool AllowPlayerTeleport(int playerid, bool allow) {
  return sampgdk_AllowPlayerTeleport(playerid, allow);
}

inline bool SetPlayerCameraPos(int playerid, float x, float y, float z) {
  return sampgdk_SetPlayerCameraPos(playerid, x, y, z);
}

inline bool SetPlayerCameraLookAt(int playerid, float x, float y, float z, int cut = CAMERA_CUT) {
  return sampgdk_SetPlayerCameraLookAt(playerid, x, y, z, cut);
}

inline bool SetCameraBehindPlayer(int playerid) {
  return sampgdk_SetCameraBehindPlayer(playerid);
}

inline bool GetPlayerCameraPos(int playerid, float * x, float * y, float * z) {
  return sampgdk_GetPlayerCameraPos(playerid, x, y, z);
}

inline bool GetPlayerCameraFrontVector(int playerid, float * x, float * y, float * z) {
  return sampgdk_GetPlayerCameraFrontVector(playerid, x, y, z);
}

inline int GetPlayerCameraMode(int playerid) {
  return sampgdk_GetPlayerCameraMode(playerid);
}

inline bool EnablePlayerCameraTarget(int playerid, bool enable) {
  return sampgdk_EnablePlayerCameraTarget(playerid, enable);
}

inline int GetPlayerCameraTargetObject(int playerid) {
  return sampgdk_GetPlayerCameraTargetObject(playerid);
}

inline int GetPlayerCameraTargetVehicle(int playerid) {
  return sampgdk_GetPlayerCameraTargetVehicle(playerid);
}

inline int GetPlayerCameraTargetPlayer(int playerid) {
  return sampgdk_GetPlayerCameraTargetPlayer(playerid);
}

inline int GetPlayerCameraTargetActor(int playerid) {
  return sampgdk_GetPlayerCameraTargetActor(playerid);
}

inline float GetPlayerCameraAspectRatio(int playerid) {
  return sampgdk_GetPlayerCameraAspectRatio(playerid);
}

inline float GetPlayerCameraZoom(int playerid) {
  return sampgdk_GetPlayerCameraZoom(playerid);
}

inline bool AttachCameraToObject(int playerid, int objectid) {
  return sampgdk_AttachCameraToObject(playerid, objectid);
}

inline bool AttachCameraToPlayerObject(int playerid, int playerobjectid) {
  return sampgdk_AttachCameraToPlayerObject(playerid, playerobjectid);
}

inline bool InterpolateCameraPos(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) {
  return sampgdk_InterpolateCameraPos(playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut);
}

inline bool InterpolateCameraLookAt(int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, int cut = CAMERA_CUT) {
  return sampgdk_InterpolateCameraLookAt(playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, cut);
}

inline bool IsPlayerConnected(int playerid) {
  return sampgdk_IsPlayerConnected(playerid);
}

inline bool IsPlayerInVehicle(int playerid, int vehicleid) {
  return sampgdk_IsPlayerInVehicle(playerid, vehicleid);
}

inline bool IsPlayerInAnyVehicle(int playerid) {
  return sampgdk_IsPlayerInAnyVehicle(playerid);
}

inline bool IsPlayerInCheckpoint(int playerid) {
  return sampgdk_IsPlayerInCheckpoint(playerid);
}

inline bool IsPlayerInRaceCheckpoint(int playerid) {
  return sampgdk_IsPlayerInRaceCheckpoint(playerid);
}

inline bool SetPlayerVirtualWorld(int playerid, int worldid) {
  return sampgdk_SetPlayerVirtualWorld(playerid, worldid);
}

inline int GetPlayerVirtualWorld(int playerid) {
  return sampgdk_GetPlayerVirtualWorld(playerid);
}

inline bool EnableStuntBonusForPlayer(int playerid, bool enable) {
  return sampgdk_EnableStuntBonusForPlayer(playerid, enable);
}

inline bool EnableStuntBonusForAll(bool enable) {
  return sampgdk_EnableStuntBonusForAll(enable);
}

inline bool TogglePlayerSpectating(int playerid, bool toggle) {
  return sampgdk_TogglePlayerSpectating(playerid, toggle);
}

inline bool PlayerSpectatePlayer(int playerid, int targetplayerid, int mode = SPECTATE_MODE_NORMAL) {
  return sampgdk_PlayerSpectatePlayer(playerid, targetplayerid, mode);
}

inline bool PlayerSpectateVehicle(int playerid, int targetvehicleid, int mode = SPECTATE_MODE_NORMAL) {
  return sampgdk_PlayerSpectateVehicle(playerid, targetvehicleid, mode);
}

inline bool StartRecordingPlayerData(int playerid, int recordtype, const char * recordname) {
  return sampgdk_StartRecordingPlayerData(playerid, recordtype, recordname);
}

inline bool StopRecordingPlayerData(int playerid) {
  return sampgdk_StopRecordingPlayerData(playerid);
}

inline bool CreateExplosionForPlayer(int playerid, float X, float Y, float Z, int type, float Radius) {
  return sampgdk_CreateExplosionForPlayer(playerid, X, Y, Z, type, Radius);
}

} // namespace sampgdk

#else /* SAMPGDK_CPP_WRAPPERS && !IN_SAMPGDK */

#undef  SetSpawnInfo
#define SetSpawnInfo sampgdk_SetSpawnInfo

#undef  SpawnPlayer
#define SpawnPlayer sampgdk_SpawnPlayer

#undef  SetPlayerPos
#define SetPlayerPos sampgdk_SetPlayerPos

#undef  SetPlayerPosFindZ
#define SetPlayerPosFindZ sampgdk_SetPlayerPosFindZ

#undef  GetPlayerPos
#define GetPlayerPos sampgdk_GetPlayerPos

#undef  SetPlayerFacingAngle
#define SetPlayerFacingAngle sampgdk_SetPlayerFacingAngle

#undef  GetPlayerFacingAngle
#define GetPlayerFacingAngle sampgdk_GetPlayerFacingAngle

#undef  IsPlayerInRangeOfPoint
#define IsPlayerInRangeOfPoint sampgdk_IsPlayerInRangeOfPoint

#undef  GetPlayerDistanceFromPoint
#define GetPlayerDistanceFromPoint sampgdk_GetPlayerDistanceFromPoint

#undef  IsPlayerStreamedIn
#define IsPlayerStreamedIn sampgdk_IsPlayerStreamedIn

#undef  SetPlayerInterior
#define SetPlayerInterior sampgdk_SetPlayerInterior

#undef  GetPlayerInterior
#define GetPlayerInterior sampgdk_GetPlayerInterior

#undef  SetPlayerHealth
#define SetPlayerHealth sampgdk_SetPlayerHealth

#undef  GetPlayerHealth
#define GetPlayerHealth sampgdk_GetPlayerHealth

#undef  SetPlayerArmour
#define SetPlayerArmour sampgdk_SetPlayerArmour

#undef  GetPlayerArmour
#define GetPlayerArmour sampgdk_GetPlayerArmour

#undef  SetPlayerAmmo
#define SetPlayerAmmo sampgdk_SetPlayerAmmo

#undef  GetPlayerAmmo
#define GetPlayerAmmo sampgdk_GetPlayerAmmo

#undef  GetPlayerWeaponState
#define GetPlayerWeaponState sampgdk_GetPlayerWeaponState

#undef  GetPlayerTargetPlayer
#define GetPlayerTargetPlayer sampgdk_GetPlayerTargetPlayer

#undef  GetPlayerTargetActor
#define GetPlayerTargetActor sampgdk_GetPlayerTargetActor

#undef  SetPlayerTeam
#define SetPlayerTeam sampgdk_SetPlayerTeam

#undef  GetPlayerTeam
#define GetPlayerTeam sampgdk_GetPlayerTeam

#undef  SetPlayerScore
#define SetPlayerScore sampgdk_SetPlayerScore

#undef  GetPlayerScore
#define GetPlayerScore sampgdk_GetPlayerScore

#undef  GetPlayerDrunkLevel
#define GetPlayerDrunkLevel sampgdk_GetPlayerDrunkLevel

#undef  SetPlayerDrunkLevel
#define SetPlayerDrunkLevel sampgdk_SetPlayerDrunkLevel

#undef  SetPlayerColor
#define SetPlayerColor sampgdk_SetPlayerColor

#undef  GetPlayerColor
#define GetPlayerColor sampgdk_GetPlayerColor

#undef  SetPlayerSkin
#define SetPlayerSkin sampgdk_SetPlayerSkin

#undef  GetPlayerSkin
#define GetPlayerSkin sampgdk_GetPlayerSkin

#undef  GivePlayerWeapon
#define GivePlayerWeapon sampgdk_GivePlayerWeapon

#undef  ResetPlayerWeapons
#define ResetPlayerWeapons sampgdk_ResetPlayerWeapons

#undef  SetPlayerArmedWeapon
#define SetPlayerArmedWeapon sampgdk_SetPlayerArmedWeapon

#undef  GetPlayerWeaponData
#define GetPlayerWeaponData sampgdk_GetPlayerWeaponData

#undef  GivePlayerMoney
#define GivePlayerMoney sampgdk_GivePlayerMoney

#undef  ResetPlayerMoney
#define ResetPlayerMoney sampgdk_ResetPlayerMoney

#undef  SetPlayerName
#define SetPlayerName sampgdk_SetPlayerName

#undef  GetPlayerMoney
#define GetPlayerMoney sampgdk_GetPlayerMoney

#undef  GetPlayerState
#define GetPlayerState sampgdk_GetPlayerState

#undef  GetPlayerIp
#define GetPlayerIp sampgdk_GetPlayerIp

#undef  GetPlayerPing
#define GetPlayerPing sampgdk_GetPlayerPing

#undef  GetPlayerWeapon
#define GetPlayerWeapon sampgdk_GetPlayerWeapon

#undef  GetPlayerKeys
#define GetPlayerKeys sampgdk_GetPlayerKeys

#undef  GetPlayerName
#define GetPlayerName sampgdk_GetPlayerName

#undef  SetPlayerTime
#define SetPlayerTime sampgdk_SetPlayerTime

#undef  GetPlayerTime
#define GetPlayerTime sampgdk_GetPlayerTime

#undef  TogglePlayerClock
#define TogglePlayerClock sampgdk_TogglePlayerClock

#undef  SetPlayerWeather
#define SetPlayerWeather sampgdk_SetPlayerWeather

#undef  ForceClassSelection
#define ForceClassSelection sampgdk_ForceClassSelection

#undef  SetPlayerWantedLevel
#define SetPlayerWantedLevel sampgdk_SetPlayerWantedLevel

#undef  GetPlayerWantedLevel
#define GetPlayerWantedLevel sampgdk_GetPlayerWantedLevel

#undef  SetPlayerFightingStyle
#define SetPlayerFightingStyle sampgdk_SetPlayerFightingStyle

#undef  GetPlayerFightingStyle
#define GetPlayerFightingStyle sampgdk_GetPlayerFightingStyle

#undef  SetPlayerVelocity
#define SetPlayerVelocity sampgdk_SetPlayerVelocity

#undef  GetPlayerVelocity
#define GetPlayerVelocity sampgdk_GetPlayerVelocity

#undef  PlayCrimeReportForPlayer
#define PlayCrimeReportForPlayer sampgdk_PlayCrimeReportForPlayer

#undef  PlayAudioStreamForPlayer
#define PlayAudioStreamForPlayer sampgdk_PlayAudioStreamForPlayer

#undef  StopAudioStreamForPlayer
#define StopAudioStreamForPlayer sampgdk_StopAudioStreamForPlayer

#undef  SetPlayerShopName
#define SetPlayerShopName sampgdk_SetPlayerShopName

#undef  SetPlayerSkillLevel
#define SetPlayerSkillLevel sampgdk_SetPlayerSkillLevel

#undef  GetPlayerSurfingVehicleID
#define GetPlayerSurfingVehicleID sampgdk_GetPlayerSurfingVehicleID

#undef  GetPlayerSurfingObjectID
#define GetPlayerSurfingObjectID sampgdk_GetPlayerSurfingObjectID

#undef  RemoveBuildingForPlayer
#define RemoveBuildingForPlayer sampgdk_RemoveBuildingForPlayer

#undef  GetPlayerLastShotVectors
#define GetPlayerLastShotVectors sampgdk_GetPlayerLastShotVectors

#undef  SetPlayerAttachedObject
#define SetPlayerAttachedObject sampgdk_SetPlayerAttachedObject

#undef  RemovePlayerAttachedObject
#define RemovePlayerAttachedObject sampgdk_RemovePlayerAttachedObject

#undef  IsPlayerAttachedObjectSlotUsed
#define IsPlayerAttachedObjectSlotUsed sampgdk_IsPlayerAttachedObjectSlotUsed

#undef  EditAttachedObject
#define EditAttachedObject sampgdk_EditAttachedObject

#undef  CreatePlayerTextDraw
#define CreatePlayerTextDraw sampgdk_CreatePlayerTextDraw

#undef  PlayerTextDrawDestroy
#define PlayerTextDrawDestroy sampgdk_PlayerTextDrawDestroy

#undef  PlayerTextDrawLetterSize
#define PlayerTextDrawLetterSize sampgdk_PlayerTextDrawLetterSize

#undef  PlayerTextDrawTextSize
#define PlayerTextDrawTextSize sampgdk_PlayerTextDrawTextSize

#undef  PlayerTextDrawAlignment
#define PlayerTextDrawAlignment sampgdk_PlayerTextDrawAlignment

#undef  PlayerTextDrawColor
#define PlayerTextDrawColor sampgdk_PlayerTextDrawColor

#undef  PlayerTextDrawUseBox
#define PlayerTextDrawUseBox sampgdk_PlayerTextDrawUseBox

#undef  PlayerTextDrawBoxColor
#define PlayerTextDrawBoxColor sampgdk_PlayerTextDrawBoxColor

#undef  PlayerTextDrawSetShadow
#define PlayerTextDrawSetShadow sampgdk_PlayerTextDrawSetShadow

#undef  PlayerTextDrawSetOutline
#define PlayerTextDrawSetOutline sampgdk_PlayerTextDrawSetOutline

#undef  PlayerTextDrawBackgroundColor
#define PlayerTextDrawBackgroundColor sampgdk_PlayerTextDrawBackgroundColor

#undef  PlayerTextDrawFont
#define PlayerTextDrawFont sampgdk_PlayerTextDrawFont

#undef  PlayerTextDrawSetProportional
#define PlayerTextDrawSetProportional sampgdk_PlayerTextDrawSetProportional

#undef  PlayerTextDrawSetSelectable
#define PlayerTextDrawSetSelectable sampgdk_PlayerTextDrawSetSelectable

#undef  PlayerTextDrawShow
#define PlayerTextDrawShow sampgdk_PlayerTextDrawShow

#undef  PlayerTextDrawHide
#define PlayerTextDrawHide sampgdk_PlayerTextDrawHide

#undef  PlayerTextDrawSetString
#define PlayerTextDrawSetString sampgdk_PlayerTextDrawSetString

#undef  PlayerTextDrawSetPreviewModel
#define PlayerTextDrawSetPreviewModel sampgdk_PlayerTextDrawSetPreviewModel

#undef  PlayerTextDrawSetPreviewRot
#define PlayerTextDrawSetPreviewRot sampgdk_PlayerTextDrawSetPreviewRot

#undef  PlayerTextDrawSetPreviewVehCol
#define PlayerTextDrawSetPreviewVehCol sampgdk_PlayerTextDrawSetPreviewVehCol

#undef  SetPVarInt
#define SetPVarInt sampgdk_SetPVarInt

#undef  GetPVarInt
#define GetPVarInt sampgdk_GetPVarInt

#undef  SetPVarString
#define SetPVarString sampgdk_SetPVarString

#undef  GetPVarString
#define GetPVarString sampgdk_GetPVarString

#undef  SetPVarFloat
#define SetPVarFloat sampgdk_SetPVarFloat

#undef  GetPVarFloat
#define GetPVarFloat sampgdk_GetPVarFloat

#undef  DeletePVar
#define DeletePVar sampgdk_DeletePVar

#undef  GetPVarsUpperIndex
#define GetPVarsUpperIndex sampgdk_GetPVarsUpperIndex

#undef  GetPVarNameAtIndex
#define GetPVarNameAtIndex sampgdk_GetPVarNameAtIndex

#undef  GetPVarType
#define GetPVarType sampgdk_GetPVarType

#undef  SetPlayerChatBubble
#define SetPlayerChatBubble sampgdk_SetPlayerChatBubble

#undef  PutPlayerInVehicle
#define PutPlayerInVehicle sampgdk_PutPlayerInVehicle

#undef  GetPlayerVehicleID
#define GetPlayerVehicleID sampgdk_GetPlayerVehicleID

#undef  GetPlayerVehicleSeat
#define GetPlayerVehicleSeat sampgdk_GetPlayerVehicleSeat

#undef  RemovePlayerFromVehicle
#define RemovePlayerFromVehicle sampgdk_RemovePlayerFromVehicle

#undef  TogglePlayerControllable
#define TogglePlayerControllable sampgdk_TogglePlayerControllable

#undef  PlayerPlaySound
#define PlayerPlaySound sampgdk_PlayerPlaySound

#undef  ApplyAnimation
#define ApplyAnimation sampgdk_ApplyAnimation

#undef  ClearAnimations
#define ClearAnimations sampgdk_ClearAnimations

#undef  GetPlayerAnimationIndex
#define GetPlayerAnimationIndex sampgdk_GetPlayerAnimationIndex

#undef  GetAnimationName
#define GetAnimationName sampgdk_GetAnimationName

#undef  GetPlayerSpecialAction
#define GetPlayerSpecialAction sampgdk_GetPlayerSpecialAction

#undef  SetPlayerSpecialAction
#define SetPlayerSpecialAction sampgdk_SetPlayerSpecialAction

#undef  DisableRemoteVehicleCollisions
#define DisableRemoteVehicleCollisions sampgdk_DisableRemoteVehicleCollisions

#undef  SetPlayerCheckpoint
#define SetPlayerCheckpoint sampgdk_SetPlayerCheckpoint

#undef  DisablePlayerCheckpoint
#define DisablePlayerCheckpoint sampgdk_DisablePlayerCheckpoint

#undef  SetPlayerRaceCheckpoint
#define SetPlayerRaceCheckpoint sampgdk_SetPlayerRaceCheckpoint

#undef  DisablePlayerRaceCheckpoint
#define DisablePlayerRaceCheckpoint sampgdk_DisablePlayerRaceCheckpoint

#undef  SetPlayerWorldBounds
#define SetPlayerWorldBounds sampgdk_SetPlayerWorldBounds

#undef  SetPlayerMarkerForPlayer
#define SetPlayerMarkerForPlayer sampgdk_SetPlayerMarkerForPlayer

#undef  ShowPlayerNameTagForPlayer
#define ShowPlayerNameTagForPlayer sampgdk_ShowPlayerNameTagForPlayer

#undef  SetPlayerMapIcon
#define SetPlayerMapIcon sampgdk_SetPlayerMapIcon

#undef  RemovePlayerMapIcon
#define RemovePlayerMapIcon sampgdk_RemovePlayerMapIcon

#undef  AllowPlayerTeleport
#define AllowPlayerTeleport sampgdk_AllowPlayerTeleport

#undef  SetPlayerCameraPos
#define SetPlayerCameraPos sampgdk_SetPlayerCameraPos

#undef  SetPlayerCameraLookAt
#define SetPlayerCameraLookAt sampgdk_SetPlayerCameraLookAt

#undef  SetCameraBehindPlayer
#define SetCameraBehindPlayer sampgdk_SetCameraBehindPlayer

#undef  GetPlayerCameraPos
#define GetPlayerCameraPos sampgdk_GetPlayerCameraPos

#undef  GetPlayerCameraFrontVector
#define GetPlayerCameraFrontVector sampgdk_GetPlayerCameraFrontVector

#undef  GetPlayerCameraMode
#define GetPlayerCameraMode sampgdk_GetPlayerCameraMode

#undef  EnablePlayerCameraTarget
#define EnablePlayerCameraTarget sampgdk_EnablePlayerCameraTarget

#undef  GetPlayerCameraTargetObject
#define GetPlayerCameraTargetObject sampgdk_GetPlayerCameraTargetObject

#undef  GetPlayerCameraTargetVehicle
#define GetPlayerCameraTargetVehicle sampgdk_GetPlayerCameraTargetVehicle

#undef  GetPlayerCameraTargetPlayer
#define GetPlayerCameraTargetPlayer sampgdk_GetPlayerCameraTargetPlayer

#undef  GetPlayerCameraTargetActor
#define GetPlayerCameraTargetActor sampgdk_GetPlayerCameraTargetActor

#undef  GetPlayerCameraAspectRatio
#define GetPlayerCameraAspectRatio sampgdk_GetPlayerCameraAspectRatio

#undef  GetPlayerCameraZoom
#define GetPlayerCameraZoom sampgdk_GetPlayerCameraZoom

#undef  AttachCameraToObject
#define AttachCameraToObject sampgdk_AttachCameraToObject

#undef  AttachCameraToPlayerObject
#define AttachCameraToPlayerObject sampgdk_AttachCameraToPlayerObject

#undef  InterpolateCameraPos
#define InterpolateCameraPos sampgdk_InterpolateCameraPos

#undef  InterpolateCameraLookAt
#define InterpolateCameraLookAt sampgdk_InterpolateCameraLookAt

#undef  IsPlayerConnected
#define IsPlayerConnected sampgdk_IsPlayerConnected

#undef  IsPlayerInVehicle
#define IsPlayerInVehicle sampgdk_IsPlayerInVehicle

#undef  IsPlayerInAnyVehicle
#define IsPlayerInAnyVehicle sampgdk_IsPlayerInAnyVehicle

#undef  IsPlayerInCheckpoint
#define IsPlayerInCheckpoint sampgdk_IsPlayerInCheckpoint

#undef  IsPlayerInRaceCheckpoint
#define IsPlayerInRaceCheckpoint sampgdk_IsPlayerInRaceCheckpoint

#undef  SetPlayerVirtualWorld
#define SetPlayerVirtualWorld sampgdk_SetPlayerVirtualWorld

#undef  GetPlayerVirtualWorld
#define GetPlayerVirtualWorld sampgdk_GetPlayerVirtualWorld

#undef  EnableStuntBonusForPlayer
#define EnableStuntBonusForPlayer sampgdk_EnableStuntBonusForPlayer

#undef  EnableStuntBonusForAll
#define EnableStuntBonusForAll sampgdk_EnableStuntBonusForAll

#undef  TogglePlayerSpectating
#define TogglePlayerSpectating sampgdk_TogglePlayerSpectating

#undef  PlayerSpectatePlayer
#define PlayerSpectatePlayer sampgdk_PlayerSpectatePlayer

#undef  PlayerSpectateVehicle
#define PlayerSpectateVehicle sampgdk_PlayerSpectateVehicle

#undef  StartRecordingPlayerData
#define StartRecordingPlayerData sampgdk_StartRecordingPlayerData

#undef  StopRecordingPlayerData
#define StopRecordingPlayerData sampgdk_StopRecordingPlayerData

#undef  CreateExplosionForPlayer
#define CreateExplosionForPlayer sampgdk_CreateExplosionForPlayer

#endif /* !SAMPGDK_CPP_WRAPPERS || IN_SAMPGDK */
#endif /* !DOXYGEN */

#endif /* !SAMPGDK_A_PLAYERS_H */
