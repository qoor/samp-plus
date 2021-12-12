/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/Common.h
 *  PURPOSE:     Common game layer include file
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#define CGAME_DLL

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <game/Common.h>

//#undef DEBUG_LOG
#ifdef DEBUG_LOG
    #include <stdio.h>
    #include <time.h>

	#include <SA-MP+/Debug.h>

static FILE* fDebugFile;

static void OutputDebugText(const char* szDebugText)
{
        #ifdef MTA_DEBUG
    /*char szDebug[500];
    sprintf(szDebug, "%s\n", szDebugText);
    OutputDebugString(szDebug);*/
	Debug::write(szDebugText);
        #endif
}

    #ifdef MTA_DEBUG
        #define DEBUG_TRACE(szText) \
            OutputDebugText(szText);
    #endif
#else
    #define DEBUG_TRACE(szText) // we do nothing with release versions
#endif
