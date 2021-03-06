/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CAnimBlendSequence.h
 *  PURPOSE:     Animation blend sequence interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

class CAnimBlendSequence
{
public:
    virtual void                           Initialize(void) = 0;
    virtual void                           SetName(const char* szName) = 0;
    virtual void                           SetBoneTag(int32_t i32BoneID) = 0;
    virtual void                           SetKeyFrames(size_t cKeyFrames, bool bRoot, bool bCompressed, void* pKeyFrames) = 0;
    virtual void*                          GetKeyFrame(size_t iFrame, uint32_t u32FrameSizeInBytes) = 0;
    virtual uint32_t                       GetHash(void) = 0;
    virtual uint16_t                       GetBoneTag(void) = 0;
    virtual BYTE*                          GetKeyFrames(void) = 0;
    virtual unsigned short                 GetKeyFramesCount(void) = 0;
    virtual bool                           IsBigChunkForAllSequences(void) = 0;
    virtual void                           CopySequenceProperties(CAnimBlendSequenceSAInterface* pAnimSequenceInterface) = 0;
    virtual CAnimBlendSequenceSAInterface* GetInterface(void) = 0;
};
