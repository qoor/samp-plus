/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/game/CAnimManager.h
 *  PURPOSE:     Animation manager interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <memory>

// Get correct values
#define MAX_ANIM_GROUPS 200
#define MAX_ANIMATIONS 500
#define MAX_ANIM_BLOCKS 200

typedef unsigned long AssocGroupId;
typedef unsigned long AnimationId;

class SString;
class CAnimBlendAssocGroup;
class CAnimBlendHierarchy;
class CAnimBlendSequence;
class CAnimBlock;
class CAnimBlendAssociation;
class CAnimBlendStaticAssociation;
class CAnimBlendStaticAssociationSAInterface;
class CClientPed;
struct RpClump;
struct RwStream;
struct AnimAssocDefinition;
struct AnimDescriptor;

class CAnimBlendAssocGroupSAInterface;
class CAnimBlendAssociationSAInterface;
class CAnimBlendHierarchySAInterface;
class CAnimBlendSequenceSAInterface;
class CAnimBlockSAInterface;

class CAnimManager
{
    friend class CAnimBlendAssociation;

public:
    typedef std::unique_ptr<CAnimBlendAssociation>       AnimBlendAssoc_type;
    typedef std::unique_ptr<CAnimBlendStaticAssociation> StaticAssocIntface_type;

    virtual void Initialize(void) = 0;
    virtual void Shutdown(void) = 0;

    virtual int GetNumAnimations(void) = 0;
    virtual int GetNumAnimBlocks(void) = 0;
    virtual int GetNumAnimAssocDefinitions(void) = 0;

    virtual std::unique_ptr<CAnimBlendHierarchy> GetAnimation(int ID) = 0;
    virtual std::unique_ptr<CAnimBlendHierarchy> GetAnimation(const char* szName, CAnimBlock* pBlock) = 0;
    virtual std::unique_ptr<CAnimBlendHierarchy> GetAnimation(unsigned int uiIndex, CAnimBlock* pBlock) = 0;

    virtual CAnimBlock* GetAnimationBlock(int ID) = 0;
    virtual CAnimBlock* GetAnimationBlock(const char* szName) = 0;
    virtual int         GetAnimationBlockIndex(const char* szName) = 0;
    virtual int         RegisterAnimBlock(const char* szName) = 0;

    virtual CAnimBlendAssocGroup* GetAnimBlendAssoc(AssocGroupId groupID) = 0;
    virtual AssocGroupId          GetFirstAssocGroup(const char* szName) = 0;

    virtual const char* GetAnimGroupName(AssocGroupId groupID) = 0;
    virtual const char* GetAnimBlockName(AssocGroupId groupID) = 0;

    virtual AnimBlendAssoc_type     CreateAnimAssociation(AssocGroupId animGroup, AnimationId animID) = 0;
    virtual StaticAssocIntface_type GetAnimStaticAssociation(AssocGroupId animGroup, AnimationId animID) = 0;
    virtual AnimBlendAssoc_type     GetAnimAssociation(AssocGroupId animGroup, const char* szAnimName) = 0;
    virtual AnimBlendAssoc_type     AddAnimation(RpClump* pClump, AssocGroupId animGroup, AnimationId animID) = 0;
    virtual AnimBlendAssoc_type     AddAnimation(RpClump* pClump, CAnimBlendHierarchy*, int ID) = 0;
    virtual AnimBlendAssoc_type     AddAnimationAndSync(RpClump* pClump, CAnimBlendAssociation* pAssociation, AssocGroupId animGroup, AnimationId animID) = 0;
    virtual AnimBlendAssoc_type     BlendAnimation(RpClump* pClump, AssocGroupId animGroup, AnimationId animID, float fBlendDelta) = 0;
    virtual AnimBlendAssoc_type     BlendAnimation(RpClump* pClump, CAnimBlendHierarchy* pHierarchy, int ID, float fBlendDelta) = 0;

    virtual void AddAnimBlockRef(int ID) = 0;
    virtual void RemoveAnimBlockRef(int ID) = 0;
    virtual void RemoveAnimBlockRefWithoutDelete(int ID) = 0;
    virtual int  GetNumRefsToAnimBlock(int ID) = 0;
    virtual void RemoveAnimBlock(int ID) = 0;

    virtual AnimAssocDefinition* AddAnimAssocDefinition(const char* szBlockName, const char* szAnimName, AssocGroupId animGroup, AnimationId animID,
                                                        AnimDescriptor* pDescriptor) = 0;
    virtual void                 ReadAnimAssociationDefinitions(void) = 0;
    virtual void                 CreateAnimAssocGroups(void) = 0;

    virtual void UncompressAnimation(CAnimBlendHierarchy* pHierarchy) = 0;
    virtual void RemoveFromUncompressedCache(CAnimBlendHierarchy* pHierarchy) = 0;
    virtual void RemoveFromUncompressedCache(CAnimBlendHierarchySAInterface* pInterface) = 0;

    virtual void  LoadAnimFile(const char* szFile) = 0;
    virtual void  LoadAnimFile(RwStream* pStream, bool b1, const char* sz1) = 0;
    virtual void  LoadAnimFiles(void) = 0;
    virtual void  RemoveLastAnimFile(void) = 0;
    virtual BYTE* AllocateKeyFramesMemory(uint32_t u32BytesToAllocate) = 0;
    virtual void  FreeKeyFramesMemory(void* pKeyFrames) = 0;

    // Non members
    virtual bool                HasAnimGroupLoaded(AssocGroupId groupID) = 0;
    virtual AnimBlendAssoc_type RpAnimBlendClumpGetFirstAssociation(RpClump* pClump) = 0;
    virtual AnimBlendAssoc_type RpAnimBlendClumpGetAssociation(RpClump* pClump, const char* szAnimName) = 0;
    virtual AnimBlendAssoc_type RpAnimBlendClumpGetAssociation(RpClump* pClump, AnimationId animID) = 0;
    virtual AnimBlendAssoc_type RpAnimBlendClumpGetAssociationHashKey(RpClump* pClump, const unsigned int& uiAnimNameHashKey) = 0;
    virtual AnimBlendAssoc_type RpAnimBlendGetNextAssociation(std::unique_ptr<CAnimBlendAssociation>& pAssociation) = 0;
    virtual int                 RpAnimBlendClumpGetNumAssociations(RpClump* pClump) = 0;
    virtual void                RpAnimBlendClumpUpdateAnimations(RpClump* pClump, float f1, bool b1) = 0;

    // MTA members
    virtual AnimBlendAssoc_type                  GetAnimBlendAssociation(CAnimBlendAssociationSAInterface* pInterface) = 0;
    virtual CAnimBlendAssocGroup*                GetAnimBlendAssocGroup(CAnimBlendAssocGroupSAInterface* pInterface) = 0;
    virtual CAnimBlock*                          GetAnimBlock(CAnimBlockSAInterface* pInterface) = 0;
    virtual std::unique_ptr<CAnimBlendHierarchy> GetAnimBlendHierarchy(CAnimBlendHierarchySAInterface* pInterface) = 0;

    virtual StaticAssocIntface_type GetAnimStaticAssociation(CAnimBlendStaticAssociationSAInterface* pInterface) = 0;

    // MTA members, but use this strictly for custom animations only
    virtual std::unique_ptr<CAnimBlendHierarchy> GetCustomAnimBlendHierarchy(CAnimBlendHierarchySAInterface* pInterface) = 0;
    virtual std::unique_ptr<CAnimBlendSequence>  GetCustomAnimBlendSequence(CAnimBlendSequenceSAInterface* pInterface) = 0;
    virtual std::unique_ptr<CAnimBlendHierarchy> GetCustomAnimBlendHierarchy(void) = 0;
    virtual std::unique_ptr<CAnimBlendSequence>  GetCustomAnimBlendSequence(void) = 0;
    virtual void                                 DeleteCustomAnimHierarchyInterface(CAnimBlendHierarchySAInterface* pInterface) = 0;
    virtual void                                 DeleteCustomAnimSequenceInterface(CAnimBlendSequenceSAInterface* pInterface) = 0;

    virtual bool           isGateWayAnimationHierarchy(CAnimBlendHierarchySAInterface* pInterface) = 0;
    virtual const SString& GetGateWayBlockName(void) = 0;
    virtual const SString& GetGateWayAnimationName(void) = 0;
};
