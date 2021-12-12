#pragma once

#include <DirectX/d3dx9.h>

#include <game_sa/CPedSA.h>
#include <game_sa/CPlayerPedSA.h>
#include <game_sa/CVehicleSA.h>

#define SAMP03d_MAX_PLAYERS					1001
#define SAMP037_MAX_PLAYERS					1004
#define SAMP_MAX_VEHICLES					2000
#define SAMP_MAX_PICKUPS					4096
#define SAMP03d_MAX_OBJECTS					1000
#define SAMP037_MAX_OBJECTS					2100
#define SAMP_MAX_GANGZONES					1024
#define SAMP_MAX_3DTEXTS					2048
#define SAMP_MAX_TEXTDRAWS					2048
#define SAMP_MAX_GANGZONES					1024
#define SAMP_MAX_PLAYER_NAME				24
#define SAMP_ALLOWED_PLAYER_NAME_LENGTH		20
#define SAMP_MAX_CLIENTCMDS					144
#define SAMP_MAX_MENUS						128
#define SAMP037_MAX_ACTORS					1000
#define SAMP037_MAX_PLAYERTEXTDRAWS			256

// Variable offsets
#define SAMP03d_CHAT_INFO_OFFSET			0x2071B8
#define SAMP03d_CHAT_INPUT_INFO_OFFSET		0x2071BC
#define SAMP03d_KILL_INFO_OFFSET			0x2071C0
#define SAMP03d_INFO_OFFSET					0x2071A8
#define SAMP03d_COLOR_OFFSET				0x2046C8
#define SAMP03d_FONT_INFO_OFFSET			0x2071AC
#define SAMP03d_DRAWING_DISTANCE			0xC3C88
#define SAMP03d_SCOREBOARD_INFO				0x2071C8
#define SAMP03d_GAMEPROCESSHOOK				0x92FC8

#define SAMP037_CHAT_INFO_OFFSET			0x21A0E4
#define SAMP037_CHAT_INPUT_INFO_OFFSET		0x21A0E8
#define SAMP037_KILL_INFO_OFFSET			0x21A0EC
#define SAMP037_INFO_OFFSET					0x21A0F8
#define SAMP037_MISC_INFO					0x21A10C
#define SAMP037_SCOREBOARD_INFO				0x21A0B4
#define SAMP037_COLOR_OFFSET				0x216378
#define SAMP037_DRAWING_DISTANCE			0xD3DCC

#define SAMP03DL_CHAT_INFO_OFFSET			0x2ACA10
#define SAMP03DL_CHAT_INPUT_INFO_OFFSET		0x2ACA14
#define SAMP03DL_KILL_INFO_OFFSET			0x2ACA18
#define SAMP03DL_INFO_OFFSET				0x2ACA24
#define SAMP03DL_COLOR_OFFSET				0x18F6C0
#define SAMP03DL_MISC_INFO					0x2ACA3C
#define SAMP03DL_DRAWING_DISTANCE			0x11812C
#define SAMP03DL_SCOREBOARD_INFO			0x2AC9DC

#define SAMP03d_FUNC_UPDATESCOREBOARDDATA	0x7540
#define SAMP03DL_FUNC_UPDATESCOREBOARDDATA	0x8C00

#define SAMP03d_PATCH_NOCARCOLORRESETTING	0xA07B0

#define SAMP03d_DRAWTEXTLABELS				0x678B1
#define SAMP037_DRAWTEXTLABELS				0x71471
#define SAMP03DL_DRAWTEXTLABELS				0x754F1

#define SAMP_INVALID_VEHICLE_ID				0xFFFF
#define SAMP_INVALID_PLAYER_ID				0xFFFF
#define SAMP_INVALID_OBJECT_ID				0xFFFF


enum eSAMP03dGameState
{
	GAMESTATE_RESTARTING_03d = 27,
	GAMESTATE_WAIT_CONNECT_03d,
	GAMESTATE_AWAIT_JOIN_03d,
	GAMESTATE_CONNECTED_03d,
	GAMESTATE_CONNECTING_03d
};

enum eSAMP037GameState
{
	GAMESTATE_WAIT_CONNECT_037 = 9,
	GAMESTATE_CONNECTING_037 = 13,
	GAMESTATE_CONNECTED_037,
	GAMESTATE_AWAIT_JOIN_037,
	GAMESTATE_RESTARTING_037 = 18
};

enum eSAMP03dPlayerState
{
	PLAYER_STATE_NONE = 0,
	PLAYER_STATE_ONFOOT = 161,
	PLAYER_STATE_PASSENGER,
	PLAYER_STATE_DRIVER,
	PLAYER_STATE_WASTED	= 208,
	PLAYER_STATE_SPAWNED
};

enum eSAMPMarkersMode
{
	PLAYER_MARKERS_MODE_OFF,
	PLAYER_MARKERS_MODE_GLOBAL,
	PLAYER_MARKERS_MODE_STREAMED
};

enum eSAMP03dSpecialAction
{
	SPECIAL_ACTION_NONE_03d,
	SPECIAL_ACTION_DUCK_03d,
	SPECIAL_ACTION_USEJETPACK_03d,
	SPECIAL_ACTION_ENTER_VEHICLE_03d,
	SPECIAL_ACTION_EXIT_VEHICLE_03d,
	SPECIAL_ACTION_DANCE1_03d,
	SPECIAL_ACTION_DANCE2_03d,
	SPECIAL_ACTION_DANCE3_03d,
	SPECIAL_ACTION_DANCE4_03d,
	SPECIAL_ACTION_HANDSUP_03d = 10,
	SPECIAL_ACTION_USECELLPHONE_03d,
	SPECIAL_ACTION_SITTING_03d,
	SPECIAL_ACTION_STOPUSECELLPHONE_03d,
	SPECIAL_ACTION_DRINK_BEER_03d = 20,
	SPECIAL_ACTION_SMOKE_CIGGY_03d,
	SPECIAL_ACTION_DRINK_WINE_03d,
	SPECIAL_ACTION_DRINK_SPRUNK_03d
};

enum eSAMP037SpecialAction
{
	SPECIAL_ACTION_NONE_037,
	SPECIAL_ACTION_DUCK_037,
	SPECIAL_ACTION_USEJETPACK_037,
	SPECIAL_ACTION_ENTER_VEHICLE_037,
	SPECIAL_ACTION_EXIT_VEHICLE_037,
	SPECIAL_ACTION_DANCE1_037,
	SPECIAL_ACTION_DANCE2_037,
	SPECIAL_ACTION_DANCE3_037,
	SPECIAL_ACTION_DANCE4_037,
	SPECIAL_ACTION_HANDSUP_037,
	SPECIAL_ACTION_USECELLPHONE_037,
	SPECIAL_ACTION_SITTING_037,
	SPECIAL_ACTION_STOPUSECELLPHONE_037,
	SPECIAL_ACTION_DRINK_BEER_037 = 20,
	SPECIAL_ACTION_SMOKE_CIGGY_037,
	SPECIAL_ACTION_DRINK_WINE_037,
	SPECIAL_ACTION_DRINK_SPRUNK_037,
	SPECIAL_ACTION_CUFFED_037,
	SPECIAL_ACTION_CARRY_037
};

#pragma pack(push, 1)
struct SAMP03d
{
	struct SAMP03dPools		*pPools;
	uint32_t				ulPort;
	char					szIP[256];
	uint8_t					pad1[2];
	char					szHostname[256];
	uint8_t					pad2[2];
	uint32_t				ulMapIcons[100];
	int						iGameState;
	uint32_t				*ulConnectTick; // not tested
	int						iLanMode; // not tested
	void					*pRakClientInterface;
	struct SAMP03dSettings	*pSettings;
};
static_assert(sizeof(SAMP03d) == 944, "Invalid size for SAMP03d");

struct SAMP037
{
	void						*pUnk0;
	struct SAMP037ServerInfo	*pServerInfo;
	uint8_t						byteSpace[24];
	char						szIP[257];
	char						szHostname[259];
	bool						bNametagStatus; // changes by /nametagstatus
	uint32_t					ulPort;
	uint32_t					ulMapIcons[100];
	int							iLanMode;
	int							iGameState;
	uint32_t					ulConnectTick;
	struct SAMP037Settings		*pSettings;
	void						*pRakClientInterface;
	struct SAMP037Pools			*pPools;
};

struct SAMP037ServerInfo
{
	uint32_t	uiIP;
	uint16_t	usPort;
};

struct SAMP03dPools
{
	struct SAMPGangzonePool			*pGangzone;
	void							*pMenu;
	struct SAMP03dPlayerPool		*pPlayer;
	struct SAMP03dVehiclePool		*pVehicle;
	struct SAMP03dTextdrawPool		*pTextdraw;
	struct SAMP03dObjectPool		*pObject;
	struct SAMPTextLabelPool		*pText3D;
	struct SAMP03dPickupPool		*pPickup;
	uint32_t						*unk;
	void							*pPlayerLabels;
};
static_assert(sizeof(SAMP03dPools) == 40, "Invalid size for SAMP03dPools");

struct SAMP037Pools
{
	struct SAMP037ActorPool		*pActor;
	struct SAMP037ObjectPool		*pObject;
	struct SAMP037GangzonePool	*pGangzone;
	struct SAMPTextLabelPool	*pText3D;
	struct SAMP037TextdrawPool	*pTextdraw;
	void					*pPlayerLabels;
	struct SAMP037PlayerPool		*pPlayer;
	struct SAMP037VehiclePool	*pVehicle;
	struct SAMP037PickupPool		*pPickup;
};

struct SAMP03dSettings
{
	uint8_t		unknown_2;
	int			iSpawnsAvailable;
	uint8_t		bytePlayerMarkersMode;
	uint8_t		bUnknown_6[7];
	uint8_t		byteShowNameTags;
	uint8_t		bUnknown_14;
	uint8_t		byteCJWalk;
	int			iUnknown3;
	float		fNameTagsDistance;
	uint8_t		bUnknown_24;
	uint8_t		byteWorldTime_Hour;
	uint8_t		byteWorldTime_Minute;
	float		fWorldBoundaries[4];
	uint8_t		byteShowZoneNames; // not tested
	uint8_t		bytePlayerClockActive;
	uint8_t		byteAllowFriendlyFire;
	uint8_t		byteSetTime;
	uint8_t		unknown_2_2;
	uint8_t		byteWeather;
	uint8_t		byteNoNametagsBehindWalls;
	float		fGravity;
	uint8_t		byteNoInteriorEnterExits; // not tested
};
static_assert(sizeof(SAMP03dSettings) == 55, "Invalid size for SAMP03dSettings");

struct SAMP03dTextdraw
{
	char		text[1024];
	char		unknown[2087];
	uint32_t	ulStyle;
	float		position[2];
	char		unknown_[16];
	int32_t		iStyleFourID;
};
static_assert(sizeof(SAMP03dTextdraw) == 3143, "Invalid size for SAMP03dTextdraw");

struct SAMP037Textdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct SAMPPickup
{
	int		iModelID;
	int		iType;
	float	fPosition[3];
};
static_assert(sizeof(SAMPPickup) == 20, "Invalid size for SAMPPickup");

struct SAMPKeys
{
	uint8_t		keys_primaryFire : 1;
	uint8_t		keys_horn__crouch : 1;
	uint8_t		keys_secondaryFire__shoot : 1;
	uint8_t		keys_accel__zoomOut : 1;
	uint8_t		keys_enterExitCar : 1;
	uint8_t		keys_decel__jump : 1;			// on foot: jump or zoom in
	uint8_t		keys_circleRight : 1;
	uint8_t		keys_aim : 1;					// hydra auto aim or on foot aim
	uint8_t		keys_circleLeft : 1;
	uint8_t		keys_landingGear__lookback : 1;
	uint8_t		keys_unknown__walkSlow : 1;
	uint8_t		keys_specialCtrlUp : 1;
	uint8_t		keys_specialCtrlDown : 1;
	uint8_t		keys_specialCtrlLeft : 1;
	uint8_t		keys_specialCtrlRight : 1;
	uint8_t		keys__unused : 1;
};
static_assert(sizeof(SAMPKeys) == 2, "Invalid size for SAMPKeys");

struct SAMPOnFootData
{
	uint16_t				sLeftRightKeys;
	uint16_t				sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct SAMPKeys		stSAMPKeys;
	};
	float					fPosition[3];
	float					fQuaternion[4];
	uint8_t					byteHealth;
	uint8_t					byteArmour;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteSpecialAction;
	float					fMoveSpeed[3];
	float					fSurfingOffsets[3];
	uint16_t				sSurfingVehicleID;
	int						sCurrentAnimationID;
};
static_assert(sizeof(SAMPOnFootData) == 68, "Invalid size for SAMPOnFootData");

struct SAMPInCarData
{
	uint16_t				sVehicleID;
	uint16_t				sLeftRightKeys;
	uint16_t				sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct SAMPKeys		stSampKeys;
	};
	float					fQuaternion[4];
	float					fPosition[3];
	float					fMoveSpeed[3];
	float					fVehicleHealth;
	uint8_t					bytePlayerHealth;
	uint8_t					byteArmor;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteSiren;
	uint8_t					byteLandingGearState;
	uint16_t				sTrailerID;
	union
	{
		uint16_t			HydraThrustAngle[2];	//nearly same value
		float				fTrainSpeed;
	};
};
static_assert(sizeof(SAMPInCarData) == 63, "Invalid size for SAMPInCarData");

struct SAMP03dAimData
{
	BYTE		byteCamMode;
	float		vecAimFrontVector[3];
	float		vecAimPos[3];
	float		fAimZAxis;
	uint8_t		byteUnknown_1[2];
};
static_assert(sizeof(SAMP03dAimData) == 31, "Invalid size for SAMP03dAimData");

struct SAMP037AimData
{
	BYTE	byteCamMode;
	float	vecAimFrontVector[3];
	float	vecAimPos[3];
	float	fAimZAxis;
	BYTE	byteCamExtZoom : 6;		// 0-63 normalized
	BYTE	byteWeaponState : 2;	// see eWeaponState
	BYTE	bUnk;
};

struct SAMP03dTrailerData
{
	uint16_t	sTrailerID;
	float		fDirection[3];
	float		fRoll[3];
	float		fPosition[3];
	float		fSpeed[3];
	uint32_t	pad; // fix alignment
};
static_assert(sizeof(SAMP03dTrailerData) == 54, "Invalid size for SAMP03dTrailerData");

struct SAMP037TrailerData
{
	uint16_t	sTrailerID;
	float		fPosition[3];
	//float		fRoll[3];
	//float		fDirection[3];
	float		fQuaternion[4]; // not tested
	float		fSpeed[3];
	float		fUnk[2];
	uint32_t	pad;
};

struct SAMPPassengerData
{
	uint16_t				sVehicleID;
	uint8_t					byteSeatID;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteHealth;
	uint8_t					byteArmor;
	uint16_t				sLeftRightKeys;
	uint16_t				sUpDownKeys;
	union
	{
		uint16_t			sKeys;
		struct SAMPKeys		stSampKeys;
	};
	float					fPosition[3];
};
static_assert(sizeof(SAMPPassengerData) == 24, "Invalid size for SAMPPassengerData");

struct SAMPDamageData
{
	uint16_t	sVehicleID_lastDamageProcessed;
	int			iBumperDamage;
	int			iDoorDamage;
	uint8_t		byteLightDamage;
	uint8_t		byteWheelDamage;
};
static_assert(sizeof(SAMPDamageData) == 12, "Invalid size for SAMPDamageData");

struct SAMP03dSurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnknown;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	int			iunknown_[2];
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};
static_assert(sizeof(SAMP03dSurfData) == 38, "Invalid size for SAMP03dSurfData");

struct SAMP037SurfData
{
	int			iIsSurfing;
	float		fSurfPosition[3];
	int			iUnk0;
	uint16_t	sSurfingVehicleID;
	uint32_t	ulSurfTick;
	struct SAMP037Vehicle *pSurfingVehicle;
	int			iUnk1;
	int			iSurfMode;	//0 = not surfing, 1 = moving (unstable surf), 2 = fixed on vehicle
};

struct SAMPHeadSync
{
	float	fHeadSync[3];
	int		iHeadSyncUpdateTick;
	int		iHeadSyncLookTick;
};
static_assert(sizeof(SAMPHeadSync) == 20, "Invalid size for SAMPHeadSync");

struct SAMP03dLocalPlayer
{
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	int						iIsActive;
	int						iIsWasted;
	struct SAMP03dPed		*pSAMP_Actor;
	struct SAMPOnFootData	onFootData;
	struct SAMPInCarData	inCarData;
	struct SAMPPassengerData passengerData;
	struct SAMP03dAimData	aimData;
	//fix trailer data
	struct SAMP03dTrailerData trailerData;
	int						iCurrentAnimID;
	uint8_t					byteUnknown_260[260];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint8_t					byteUnknown_529[34];
	uint8_t					byteUnknown_563;
	int						iSpawnSkin;
	uint8_t					unknown_568;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID;
	uint8_t					byteUnknown_630[2];
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid; // player id we are aiming at
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	struct SAMPHeadSync		headSyncData;
	uint32_t				ulUnknownTick;
	struct SAMPDamageData	vehicleDamageData;
	uint8_t					byteUnknown_756[4];
	uint8_t					byteSpectatingUnk; // 15[?],14[?],(3-Veh/4-Player [follow]) // not tested
	uint8_t					byteSpectatingWHAT; // 2 = Veh, 1 = Player // not tested
	int						iSpectateID;
	int						iInitiatedSpectating;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulZoneNameTick;

	// not placed correctly:
	uint32_t				ulUnoccupiedTick;
	struct SAMP03dSurfData	surfData;
};
static_assert(sizeof(SAMP03dLocalPlayer) == 832, "Invalid size for SAMP03dLocalPlayer");

struct SAMP03dRemotePlayerData
{
	uint16_t				sVehicleID;
	uint8_t					byteSeatID; // not tested
	int						iPassengerDriveBy;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;
	int						iUnknown_3;
	uint16_t				sPlayerID;
	struct SAMPPassengerData passengerData;
	struct SAMP03dAimData	aimData;
	struct SAMP03dTrailerData trailerData;
	struct SAMPInCarData	inCarData;
	struct SAMPOnFootData	onFootData;
	uint8_t					byteUnknown_255[88];
	uint8_t					bUnk1;
	uint32_t				dwTick;
	uint32_t				dwLastStreamedInTick; // is 0 when currently streamed in
	uint32_t				dwUnknown_18;
	int						iShowNameTag;
	int						iHasJetPack;
	uint8_t					byteSpecialAction;
	float					fActorHealth;
	float					fActorArmor;
	int						iUnknown_2;
	struct SAMP03dPed		*pSAMP_Actor;
	struct SAMP03dVehicle	*pSAMP_Vehicle;
	uint8_t					byteUnknown_385[12];
	struct SAMPHeadSync		headSyncData;
	uint8_t					byteUnknown_77[16];
	float					fOnFootPos[3]; // lag comp copies of original onfoot/incar vars
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	float					fVehicleRoll[4];
	uint8_t					byteUnknown_393[24];

	// not placed correctly (but also currently not used):
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};
static_assert(sizeof(SAMP03dRemotePlayerData) == 541, "Invalid size for SAMP03dRemotePlayerData");

struct SAMP037RemotePlayerData
{
	struct SAMP037Ped		*pSAMP_Actor;
	struct SAMP037Vehicle	*pSAMP_Vehicle;
	uint8_t					byteTeamID;
	uint8_t					bytePlayerState;
	uint8_t					byteSeatID;
	uint32_t				ulUnk3;
	int						iPassengerDriveBy;
	void					*pUnk0;
	uint8_t					byteUnk1[60];
	float					fSomething[3];
	float					fVehicleRoll[4];
	uint32_t				ulUnk2[3];
	float					fOnFootPos[3];
	float					fOnFootMoveSpeed[3];
	float					fVehiclePosition[3];
	float					fVehicleMoveSpeed[3];
	uint16_t				sPlayerID;
	uint16_t				sVehicleID;
	uint32_t				ulUnk5;
	int						iShowNameTag;
	int						iHasJetPack;
	uint8_t					byteSpecialAction;
	uint32_t				ulUnk4[3];
	struct SAMPOnFootData	onFootData;
	struct SAMPInCarData	inCarData;
	struct SAMP037TrailerData trailerData;
	struct SAMPPassengerData passengerData;
	struct SAMP037AimData	aimData;
	float					fActorArmor;
	float					fActorHealth;
	uint32_t				ulUnk10;
	uint8_t					byteUnk9;
	uint32_t				dwTick;
	uint32_t				dwLastStreamedInTick;	// is 0 when currently streamed in
	uint32_t				ulUnk7;
	int						iAFKState;
	struct SAMPHeadSync		headSyncData;
	int						iGlobalMarkerLoaded;
	int						iGlobalMarkerLocation[3];
	uint32_t				ulGlobalMarker_GTAID;
};

struct SAMP037LocalPlayer
{
	struct stSAMPPed		*pSAMP_Actor;
	uint16_t				sCurrentAnimID;
	uint16_t				sAnimFlags;
	uint32_t				ulUnk0;
	int						iIsActive;
	int						iIsWasted;
	uint16_t				sCurrentVehicleID;
	uint16_t				sLastVehicleID;
	struct SAMPOnFootData	onFootData;
	struct SAMPPassengerData passengerData;
	struct SAMP037TrailerData trailerData;
	struct SAMPInCarData	inCarData;
	struct SAMP037AimData	aimData;
	uint8_t					byteTeamID;
	int						iSpawnSkin;
	uint8_t					byteUnk1;
	float					fSpawnPos[3];
	float					fSpawnRot;
	int						iSpawnWeapon[3];
	int						iSpawnAmmo[3];
	int						iIsActorAlive;
	int						iSpawnClassLoaded;
	uint32_t				ulSpawnSelectionTick;
	uint32_t				ulSpawnSelectionStart;
	int						iIsSpectating;
	uint8_t					byteTeamID2;
	uint16_t				usUnk2;
	uint32_t				ulSendTick;
	uint32_t				ulSpectateTick;
	uint32_t				ulAimTick;
	uint32_t				ulStatsUpdateTick;
	uint32_t				ulWeapUpdateTick;
	uint16_t				sAimingAtPid;
	uint16_t				usUnk3;
	uint8_t					byteCurrentWeapon;
	uint8_t					byteWeaponInventory[13];
	int						iWeaponAmmo[13];
	int						iPassengerDriveBy;
	uint8_t					byteCurrentInterior;
	int						iIsInRCVehicle;
	uint16_t				sTargetObjectID;
	uint16_t				sTargetVehicleID;
	uint16_t				sTargetPlayerID;
	struct SAMPHeadSync		headSyncData;
	uint32_t				ulHeadSyncTick;
	BYTE					byteSpace3[260];
	struct SAMP037SurfData	surfData;
	int						iClassSelectionOnDeath;
	int						iSpawnClassID;
	int						iRequestToSpawn;
	int						iIsInSpawnScreen;
	uint32_t				ulUnk4;
	uint8_t					byteSpectateMode;		// 3 = vehicle, 4 = player, side = 14, fixed = 15
	uint8_t					byteSpectateType;		// 0 = none, 1 = player, 2 = vehicle
	int						iSpectateID;
	int						iInitiatedSpectating;
	struct SAMPDamageData	vehicleDamageData;
};

struct SAMP03dRemotePlayer
{
	void				*pVTBL_txtHandler;
	union
	{
		char	szPlayerName[16];
		char	*pszPlayerName;
	};
	int					iStrlenName__; // ?
	int					iStrlenName; // iStrlenNameMax, numByteReserved?
	int					iPing;
	int					iScore;
	SAMP03dRemotePlayerData	*pPlayerData;
	int					iIsNPC;
};
static_assert(sizeof(SAMP03dRemotePlayer) == 44, "Invalid size for SAMP03dRemotePlayer");

struct SAMP037RemotePlayer
{
	struct SAMP037RemotePlayerData *pPlayerData;
	int					iIsNPC;
	void				*pVTBL_txtHandler;
	std::string			strPlayerName;
	int					iScore;
	int					iPing;
};

template <typename T>
struct SAMPEntity
{
	void		*pVTBL;
	uint8_t		byteUnk0[60];
	T			*pGTAEntity;
	uint32_t	ulGTAEntityHandle;
};

struct SAMP03dPed : public SAMPEntity<CPedSAInterface>
{
	int					usingCellPhone;
	CPedSAInterface		*pGTA_Ped;
	uint8_t				byteUnknown_80[8];
	uint8_t				byteKeysId;
	uint8_t				pad[544];
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	int					isUrinating;
	uint32_t			ulGTA_UrinateParticle_ID;
	uint8_t				byteUnknown_3[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
};
static_assert(sizeof(SAMP03dPed) == 670, "Invalid size for SAMP03dPed");

struct SAMP037Ped : public SAMPEntity<CPedSAInterface>
{
	int					usingCellPhone;
	uint8_t				byteUnk0[600];
	CPedSAInterface		*pGTA_Ped;
	uint8_t				byteUnk1[22];
	uint8_t				byteKeysId;
	uint16_t			ulGTA_UrinateParticle_ID;
	int					DrinkingOrSmoking;
	int					object_in_hand;
	int					drunkLevel;
	uint8_t				byteUnk2[5];
	int					isDancing;
	int					danceStyle;
	int					danceMove;
	uint8_t				byteUnk3[20];
	int					isUrinating;
};

struct SAMP03dVehicle : public SAMPEntity<CVehicleSAInterface>
{
	CVehicleSAInterface *pGTA_Vehicle;
	int					iIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteUnknown_88[8];
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnknown_101[24];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};
static_assert(sizeof(SAMP03dVehicle) == 135, "Invalid size for SAMP03dVehicle");

struct SAMP037Vehicle : public SAMPEntity<CVehicleSAInterface>
{
	uint32_t			bUnk0;
	CVehicleSAInterface *pGTA_Vehicle;
	uint8_t				byteUnk1[8];
	int					bIsMotorOn;
	int					iIsLightsOn;
	int					iIsLocked;
	uint8_t				byteIsObjective;
	int					iObjectiveBlipCreated;
	uint8_t				byteUnk2[16];
	uint8_t				byteColor[2];
	int					iColorSync;
	int					iColor_something;
};

struct SAMP03dObject
{
	void				*pVTBL_Object;
	uint8_t				pad[60];
	CObjectSAInterface	*pGTAObject;
	uint32_t			ulGTA_Object_ID;
};
static_assert(sizeof(SAMP03dObject) == 72, "Invalid size for SAMP03dObject");

struct SAMP037Object : public SAMPEntity<CObjectSAInterface>
{
	uint8_t				byteUnk0[2];
	uint32_t			ulUnk1;
	int					iModel;
	uint16_t			byteUnk2;
	float				fDrawDistance;
	float				fUnk;
	float				fPos[3];
	uint8_t				byteUnk3[68];
	uint8_t				byteUnk4;
	float				fRot[3];
};

struct SAMP03dPickupPool
{
	int						iPickupID[SAMP_MAX_PICKUPS];
	int						iTimePickup[SAMP_MAX_PICKUPS];
	uint8_t					unk[SAMP_MAX_PICKUPS * 3];
	struct SAMPPickup		pickup[SAMP_MAX_PICKUPS];
	uint32_t				iCount;
	uint32_t				ul_GTA_PickupID[SAMP_MAX_PICKUPS];
};
static_assert(sizeof(SAMP03dPickupPool) == 143364, "Invalid size for SAMP03dPickupPool");

struct SAMP037PickupPool
{
	int					iPickupsCount;
	uint32_t			ul_GTA_PickupID[SAMP_MAX_PICKUPS];
	int					iPickupID[SAMP_MAX_PICKUPS];
	int					iTimePickup[SAMP_MAX_PICKUPS];
	uint8_t				unk[SAMP_MAX_PICKUPS * 3];
	struct SAMPPickup	pickup[SAMP_MAX_PICKUPS];
};

struct SAMP03dPlayerPool
{
	void						*pVTBL_txtHandler;
	union
	{
		char					szLocalPlayerName[16];
		char					*pszLocalPlayerName;
	};
	int							iStrlen_LocalPlayerName;
	int							iScoreboard_something;
	struct SAMP03dLocalPlayer	*pLocalPlayer;
	int							iIsListed[SAMP03d_MAX_PLAYERS];
	struct SAMP03dRemotePlayer	*pRemotePlayer[SAMP03d_MAX_PLAYERS];
	int							iLocalPlayerScore;
	int							iLocalPlayerPing;
	uint16_t					sLocalPlayerID;
};
static_assert(sizeof(SAMP03dPlayerPool) == 8050, "Invalid size for SAMP03dPlayerPool");

struct SAMP037PlayerPool
{
	uint32_t					ulMaxPlayerID;
	uint16_t					sLocalPlayerID;
	void						*pVTBL_txtHandler;
	std::string					strLocalPlayerName;
	struct SAMP037LocalPlayer	*pLocalPlayer;
	int							iLocalPlayerPing;
	int							iLocalPlayerScore;
	struct SAMP037RemotePlayer	*pRemotePlayer[SAMP037_MAX_PLAYERS];
	int							iIsListed[SAMP037_MAX_PLAYERS];
	DWORD						dwPlayerIP[SAMP037_MAX_PLAYERS]; // always 0
};

struct SAMP03dVehiclePool
{
	uint8_t					pad0unk[300];
	uint16_t				pad1unk[SAMP_MAX_VEHICLES];
	uint16_t				padXunk[SAMP_MAX_VEHICLES];
	int						pad2unk[SAMP_MAX_VEHICLES];
	int						pad3unk[SAMP_MAX_VEHICLES];
	int						pad4unk[SAMP_MAX_VEHICLES];
	int						pad5unk[SAMP_MAX_VEHICLES];
	CVehicleSAInterface		*pGTA_Vehicle[SAMP_MAX_VEHICLES];
	struct SAMP03dVehicle	*pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated; // not tested
};
static_assert(sizeof(SAMP03dVehiclePool) == 88304, "Invalid size for SAMP03dVehiclePool");

struct SAMP037VehiclePool
{
	int						iVehicleCount;
	void					*pUnk0;
	uint8_t					byteSpace1[0x112C];
	struct SAMP037Vehicle	*pSAMP_Vehicle[SAMP_MAX_VEHICLES];
	int						iIsListed[SAMP_MAX_VEHICLES];
	CVehicleSAInterface		*pGTA_Vehicle[SAMP_MAX_VEHICLES];
	uint8_t					byteSpace2[SAMP_MAX_VEHICLES * 6];
	uint32_t				ulShit[SAMP_MAX_VEHICLES];
	int						iIsListed2[SAMP_MAX_VEHICLES];
	uint32_t				byteSpace3[SAMP_MAX_VEHICLES * 2];
	float					fSpawnPos[SAMP_MAX_VEHICLES][3];
	int						iInitiated;
};

struct SAMP03dObjectPool
{
	struct SAMP03dObject	*object[SAMP03d_MAX_OBJECTS];
	int						iIsListed[SAMP03d_MAX_OBJECTS];
};
static_assert(sizeof(SAMP03dObjectPool) == 8000, "Invalid size for SAMP03dObjectPool");

struct SAMP03dTextdrawPool
{
#pragma pack( 1 )
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	struct SAMP03dTextdraw	*textdraw[SAMP_MAX_TEXTDRAWS];
};
static_assert(sizeof(SAMP03dTextdrawPool) == 16384, "Invalid size for SAMP03dTextdrawPool");

struct SAMP037TextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP037_MAX_PLAYERTEXTDRAWS];
	struct SAMP037Textdraw	*textdraw[SAMP_MAX_TEXTDRAWS];
	struct SAMP037Textdraw	*playerTextdraw[SAMP037_MAX_PLAYERTEXTDRAWS];
};

struct SAMPGangzone
{
	float	fPosition[4];
	DWORD	dwColor;
	DWORD	dwAltColor;
};
static_assert(sizeof(SAMPGangzone) == 24, "Invalid size for SAMPGangzone");

struct SAMPGangzonePool
{
	struct SAMPGangzone	*pGangzone[SAMP_MAX_GANGZONES];
	int					iIsListed[SAMP_MAX_GANGZONES];
};
static_assert(sizeof(SAMPGangzonePool) == 8192, "Invalid size for SAMPGangzonePool");

struct SAMPTextLabel
{
	char		*pText;
	DWORD		color;
	float		fPosition[3];
	float		fMaxViewDistance;
	uint8_t		byteShowBehindWalls;
	uint16_t	sAttachedToPlayerID;
	uint16_t	sAttachedToVehicleID;
};
static_assert(sizeof(SAMPTextLabel) == 29, "Invalid size for SAMPTextLabel");

struct SAMPTextLabelPool
{
	struct SAMPTextLabel	textLabel[SAMP_MAX_3DTEXTS];
	int						iIsListed[SAMP_MAX_3DTEXTS];
};
static_assert(sizeof(SAMPTextLabelPool) == 67584, "Invalid size for SAMP03dTextLabelPool");

struct SAMP03dChatEntry
{
	int			iType;			// 10 - text + prefix, 11 - text (server msg), 12 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
};
static_assert(sizeof(SAMP03dChatEntry) == 252, "Invalid size for SAMP03dChatEntry");

struct SAMP037ChatEntry
{
	uint32_t	SystemTime;
	char		szPrefix[28];
	char		szText[144];
	uint8_t		unknown[64];
	int			iType;			// 2 - text + prefix, 4 - text (server msg), 8 - text (debug)
	D3DCOLOR	clTextColor;
	D3DCOLOR	clPrefixColor;	// or textOnly colour
};

struct SAMP037FontRenderer
{
	ID3DXFont			*m_pChatFont;
	ID3DXFont			*m_pLittleFont;
	ID3DXFont			*m_pChatShadowFont;
	ID3DXFont			*m_pLittleShadowFont;
	ID3DXFont			*m_pCarNumberFont;
	ID3DXSprite			*m_pTempSprite;
	IDirect3DDevice9	*m_pD3DDevice;
	char				*m_pszTextBuffer;
};

struct SAMP03dChatInfo
{
	int					iChatWindowMode;			// 2 - normal, 1 - light, 0 - disabled
	uint8_t				bTimestamps;
	uint8_t				unknown[4];
	char				logFilePathChatLog[MAX_PATH + 1];
	struct SAMP03dChatEntry	chatEntry[100];
	D3DCOLOR			clTextColor;
	D3DCOLOR			clDebugColor;
	D3DCOLOR			clInfoColor;
	DWORD				dwChatboxOffset;
	int					pagesize;
	uint8_t				unknown_2[12];
	void				*pChatbox_unknown[3]; // probably classes that handle fonts/sprites
	uint8_t				unknown_3[4];
	DWORD				dwChatLinesHeight;
	DWORD				dwDistanceTextToTimestamp;
};
static_assert(sizeof(SAMP03dChatInfo) == 25526, "Invalid size for SAMP03dChatInfo");

struct SAMP037ChatInfo
{
	int					pagesize;
	char				*pLastMsgText;
	int					iChatWindowMode;
	uint8_t				bTimestamps;
	uint32_t			m_iLogFileExist;
	char				logFilePathChatLog[MAX_PATH + 1];
	void				*pGameUI; // CDXUTDialog
	void				*pEditBackground; // CDXUTEditBox
	void				*pDXUTScrollBar;
	D3DCOLOR			clTextColor;
	D3DCOLOR			clInfoColor;
	D3DCOLOR			clDebugColor;
	DWORD				m_lChatWindowBottom;
	struct SAMP037ChatEntry	chatEntry[100];
	struct SAMP037FontRenderer *m_pFontRenderer;
	ID3DXSprite			*m_pChatTextSprite;
	ID3DXSprite			*m_pSprite;
	IDirect3DDevice9	*m_pD3DDevice;
	int				m_iRenderMode; // 0 - Direct Mode (slow), 1 - Normal mode
	ID3DXRenderToSurface	*pID3DXRenderToSurface;
	IDirect3DTexture9	*m_pTexture;
	IDirect3DSurface9	*pSurface;
	D3DDISPLAYMODE		*pD3DDisplayMode;
	int					iUnk1[3];
	int					iUnk2; // smth related to drawing in direct mode
	int					m_iRedraw;
	int					m_nPrevScrollBarPosition;
	int					m_iFontSizeY;
	int					m_iTimestampWidth;
};

struct SAMPInputBox
{
	void	*pUnknown;
	uint8_t	bIsChatboxOpen;
	uint8_t	bIsMouseInChatbox;
	uint8_t	bMouseClick_related;
	uint8_t	unknown;
	DWORD	dwPosChatInput[2];
	uint8_t	unknown2[263];
	int		iCursorPosition;
	uint8_t	unknown3;
	int		iMarkedText_startPos; // Highlighted text between this and iCursorPosition
	uint8_t	unknown4[20];
	int		iMouseLeftButton;
};
static_assert(sizeof(SAMPInputBox) == 312, "Invalid size for SAMPInputBox");

typedef void(__cdecl *SAMPCMDProc)(PCHAR);

struct SAMPInputInfo
{
	void			*pD3DDevice;
	void			*pDXUTDialog;
	SAMPInputBox	*pDXUTEditBox;
	SAMPCMDProc 	pszCMDs[SAMP_MAX_CLIENTCMDS];
	char			szCMDNames[SAMP_MAX_CLIENTCMDS][33];
	int				iCMDCount;
	int				iInputEnabled;
	char			szInputBuffer[129];
	char			szRecallBufffer[10][129];
	char			szCurrentBuffer[129];
	int				iCurrentRecall;
	int				iTotalRecalls;
	SAMPCMDProc 	pszDefaultCMD;
};
static_assert(sizeof(SAMPInputInfo) == 6908, "Invalid size for SAMPInputInfo");

struct SAMPKillEntry
{
	char		szKiller[25];
	char		szVictim[25];
	D3DCOLOR	clKillerColor;
	D3DCOLOR	clVictimColor;
	uint8_t		byteType;
};
static_assert(sizeof(SAMPKillEntry) == 59, "Invalid size for SAMPKillEntry");

struct SAMP03dKillInfo
{
	int						iEnabled;
	struct SAMPKillEntry	killEntry[5];
};
static_assert(sizeof(SAMP03dKillInfo) == 299, "Invalid size for SAMP03dKillInfo");

struct SAMP037KillInfo
{
	int					iEnabled;
	struct SAMPKillEntry killEntry[5];
	int 			iLongestNickLength;
	int 			iOffsetX;
	int 			iOffsetY;

	ID3DXFont		*pD3DFont;
	ID3DXFont		*pWeaponFont1;
	ID3DXFont		*pWeaponFont2;
	ID3DXSprite		*pSprite;
	IDirect3DDevice9 *pD3DDevice;
	int 			iAuxFontInited;
	ID3DXFont 		*pAuxFont1;
	ID3DXFont 		*pAuxFont2;
};

struct SAMP037KillEntry
{
	int					iEnabled;
	struct SAMPKillEntry killEntry[5];
	int 				iLongestNickLength;
	int 				iOffsetX;
	int 				iOffsetY;

	ID3DXFont			*pD3DFont;
	ID3DXFont			*pWeaponFont1;
	ID3DXFont			*pWeaponFont2;
	ID3DXSprite			*pSprite;
	IDirect3DDevice9	*pD3DDevice;
	int 				iAuxFontInited;
	ID3DXFont 			*pAuxFont1;
	ID3DXFont 			*pAuxFont2;
};

struct SAMPChatPlayer
{
	int			iCreated;
	char		probablyTheText[256]; // text max length = 144
	DWORD		dwTickCreated;
	DWORD		dwLiveLength;
	DWORD		dwColor;
	float		fDrawDistance;
	DWORD		dwUnknown;
};
static_assert(sizeof(SAMPChatPlayer) == 280, "Invalid size for SAMPChatPlayer");

struct SAMP03dChatBubbleInfo
{
	struct SAMPChatPlayer	chatBubble[SAMP03d_MAX_PLAYERS];
};
static_assert(sizeof(SAMP03dChatBubbleInfo) == 280280, "Invalid size for SAMP03dChatBubbleInfo");

struct SAMP037ChatBubbleInfo
{
	struct SAMPChatPlayer	chatBubble[SAMP037_MAX_PLAYERS];
};

struct SAMP03dStreamedOutPlayerInfo
{
	int		iPlayerID[SAMP03d_MAX_PLAYERS];
	float	fPlayerPos[SAMP03d_MAX_PLAYERS][3];
};
static_assert(sizeof(SAMP03dStreamedOutPlayerInfo) == 16016, "Invalid size for SAMP03dStreamedOutPlayerInfo");

struct SAMP037StreamedOutPlayerInfo
{
	int		iPlayerID[SAMP037_MAX_PLAYERS];
	float	fPlayerPos[SAMP037_MAX_PLAYERS][3];
};

struct SAMP037ActorInfo
{
	int					iLastActorID;
	SAMPEntity<void>	*pActor[SAMP037_MAX_ACTORS]; // ?
	int					iIsListed[SAMP037_MAX_ACTORS];
	struct actor_info	*pGTAPed[SAMP037_MAX_ACTORS];
	uint32_t			ulUnk0[SAMP037_MAX_ACTORS];
	uint32_t			ulUnk1[SAMP037_MAX_ACTORS];
};

struct SAMP037Audio
{
	int iSoundState;
};

struct SAMP037ScoreboardInfo
{
	int					iIsEnabled;
	int					iPlayersCount;
	float				fTextOffset[2];
	float				fScalar;
	float				fSize[2];
	float				fUnk0[5];
	IDirect3DDevice9	*pDirectDevice;
	class _CDXUTDialog	*pDialog;
	class _CDXUTListBox *pList;
	int					iOffset;		// ?
	int					iIsSorted;		// ?
};

struct SAMP037GameInfo
{
	struct SAMP037Camera
	{
		void*	pEntity; // attached entity
		class CMatrix_Padded* matrix;
	};

	struct SAMP037Audio*	pAudio;
	struct SAMP037Camera*	pCamera;
	struct SAMP037Ped*	pLocalPlayerPed;
	float		fCheckpointPos[3];
	float		fCheckpointExtent[3];
	int			bCheckpointsEnabled;

	// not tested
	DWORD		dwCheckpointMarker;
	float		fRaceCheckpointPos[3];
	float		fRaceCheckpointNext[3];
	float		m_fRaceCheckpointSize;
	uint8_t		byteRaceType;

	int			bRaceCheckpointsEnabled;

	// not tested
	DWORD		dwRaceCheckpointMarker;
	DWORD		dwRaceCheckpointHandle;

	int			iCursorMode;
	uint32_t	ulUnk1;
	int			bClockEnabled;
	uint32_t	ulUnk2;
	int			bHeadMove;
	uint32_t		ulFpsLimit;
	uint8_t		byteUnk3;
	uint8_t		byteVehicleModels[212];
};

#pragma pack(pop)
