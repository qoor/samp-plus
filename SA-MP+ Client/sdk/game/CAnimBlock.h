/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CAnimBlock.h
 *  PURPOSE:     Animation block interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

enum EModelRequestType
{
    BLOCKING,
    NON_BLOCKING
};

class CAnimBlockSAInterface;
class CAnimBlendHierarchySAInterface;

class CAnimBlock
{
public:
    virtual CAnimBlockSAInterface*          GetInterface(void) = 0;
    virtual char*                           GetName(void) = 0;
    virtual int                             GetIndex(void) = 0;
    virtual void                            AddRef(void) = 0;
    virtual unsigned short                  GetRefs(void) = 0;
    virtual bool                            IsLoaded(void) = 0;
    virtual int                             GetIDOffset(void) = 0;
    virtual size_t                          GetAnimationCount(void) = 0;
    virtual void                            Request(EModelRequestType requestType, bool bAllowBlockingFail = false) = 0;
    virtual CAnimBlendHierarchySAInterface* GetAnimationHierarchyInterface(size_t iAnimation) = 0;
};
