/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/C3DMarkersSA.h
 *  PURPOSE:     Header file for 3D Marker entity manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#ifdef GTASA_30

#define FUNC_PlaceMarker        0x756D60
#define ARRAY_3D_MARKERS        0xCEA2F0

#else

#define FUNC_PlaceMarker        0x725120 // ##SA##
#define ARRAY_3D_MARKERS        0xC7DD58

#endif

#define MAX_3D_MARKERS          32

#include <game/C3DMarkers.h>
#include "C3DMarkerSA.h"

class C3DMarkerVC;

class C3DMarkersSA : public C3DMarkers
{
private:
    C3DMarkerSA* Markers[MAX_3D_MARKERS];

public:
    // constructor
    C3DMarkersSA();
    ~C3DMarkersSA(void);

    C3DMarker* CreateMarker(DWORD Identifier, e3DMarkerType dwType, CVector* vecPosition, FLOAT fSize, FLOAT fPulseFraction, BYTE r, BYTE g, BYTE b, BYTE a);
    C3DMarker* FindFreeMarker();
    C3DMarker* FindMarker(DWORD Identifier);
};
