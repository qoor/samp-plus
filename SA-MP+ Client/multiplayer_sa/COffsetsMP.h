/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        multiplayer_sa/COffsets.h
 *  PURPOSE:     Grand Theft Auto executable offsets class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

class COffsetsMP
{
public:
    static void Initialize10EU(void);
    static void Initialize10US(void);
    static void Initialize11(void);
    static void Initialize20(void);

private:
    static void InitializeCommon10(void);
};
