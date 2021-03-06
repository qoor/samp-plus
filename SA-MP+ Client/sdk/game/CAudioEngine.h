/*****************************************************************************
 *
 *  PROJECT:        Multi Theft Auto v1.0
 *  LICENSE:        See LICENSE in the top level directory
 *  FILE:        sdk/game/CAudio.h
 *  PURPOSE:        Game audio interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <windows.h>
#include "CVehicle.h"

class CEntitySAInterface;

struct SWorldSoundEvent
{
    unsigned int        uiGroup;
    unsigned int        uiIndex;
    CEntitySAInterface* pGameEntity;
    CVector             vecPosition;
};

using WorldSoundHandler = bool(const SWorldSoundEvent& event);

enum eSurfaceType
{
    SURFACE_TYPE_WATER_SHALLOW = 39,
};

enum eWeaponEventType
{
    WEAPON_EVENT_FIRE = 145,
    WEAPON_EVENT_RELOAD,
    WEAPON_EVENT_RELOAD_2,
    WEAPON_EVENT_PROJECTILE,
};

enum eAmbientSoundType
{
    AMBIENT_SOUND_GENERAL,
    AMBIENT_SOUND_GUNFIRE,
};

class CAudioEngine
{
public:
    virtual VOID          PlayFrontEndSound(DWORD dwSound) = 0;
    virtual VOID          PlayBeatTrack(short iTrack) = 0;
    virtual VOID          SetEffectsMasterVolume(BYTE bVolume) = 0;            // 64 = max volume
    virtual VOID          SetMusicMasterVolume(BYTE bVolume) = 0;
    virtual VOID          ClearMissionAudio(int slot = 1) = 0;
    virtual VOID          PreloadMissionAudio(unsigned short usAudioEvent, int slot = 1) = 0;
    virtual unsigned char GetMissionAudioLoadingStatus(int slot = 1) = 0;
    virtual bool          IsMissionAudioSampleFinished(int slot = 1) = 0;
    virtual VOID          AttachMissionAudioToPhysical(CPhysical* physical, int slot = 1) = 0;
    virtual VOID          SetMissionAudioPosition(CVector* position, int slot = 1) = 0;
    virtual bool          PlayLoadedMissionAudio(int slot = 1) = 0;
    virtual VOID          PauseAllSound(bool bPaused) = 0;
    virtual VOID          StopRadio(void) = 0;
    virtual VOID          StartRadio(unsigned int station) = 0;
    virtual void          PauseAmbientSounds(bool bPaused) = 0;
    virtual VOID          SetAmbientSoundEnabled(eAmbientSoundType eType, bool bEnabled) = 0;
    virtual bool          IsAmbientSoundEnabled(eAmbientSoundType eType) = 0;
    virtual void          ResetAmbientSounds(void) = 0;
    virtual VOID          SetWorldSoundEnabled(uint uiGroup, uint uiIndex, bool bEnabled, bool bForceCancel) = 0;
    virtual bool          IsWorldSoundEnabled(uint uiGroup, uint uiIndex) = 0;
    virtual void          ResetWorldSounds(void) = 0;
    virtual void          SetWorldSoundHandler(WorldSoundHandler* pHandler) = 0;
    virtual void          ReportBulletHit(CEntity* pEntity, unsigned char ucSurfaceType, CVector* pvecPosition, float f_2) = 0;
    virtual void          ReportWeaponEvent(int iEvent, eWeaponType weaponType, CPhysical* pPhysical) = 0;
};
