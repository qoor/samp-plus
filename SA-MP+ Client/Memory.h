#pragma once

#define ASM_JMP 0xE9
#define ASM_NOP 0x90

typedef unsigned int uint;

// Auto detect requirement of US/EU hook installation
#define EZHookInstall(type) \
        __if_not_exists( RETURN_##type##_US ) \
        { \
            HookInstall( HOOKPOS_##type, (DWORD)HOOK_##type, HOOKSIZE_##type ) \
        } \
        __if_exists( RETURN_##type##_US ) \
        { \
            if ( pGameInterface->GetGameVersion () == VERSION_US_10 ) \
            { \
                EZHookInstall_HERE( type, US ) \
            } \
            else \
            { \
                EZHookInstall_HERE( type, EU ) \
            } \
        }

// US/EU hook installation
// Includes additional return pointer copies if required
#define EZHookInstall_HERE(type,CO) \
        __if_exists( RESTORE_Bytes_##type ) \
        { \
            RESTORE_Addr_##type = HOOKPOS_##type##_##CO##; \
            RESTORE_Size_##type = HOOKSIZE_##type##_##CO##; \
            assert( sizeof(RESTORE_Bytes_##type) >= RESTORE_Size_##type ); \
            MemCpyFast ( RESTORE_Bytes_##type, (PVOID)RESTORE_Addr_##type, RESTORE_Size_##type ); \
        } \
        HookInstall( HOOKPOS_##type##_##CO##, (DWORD)HOOK_##type, HOOKSIZE_##type##_##CO## ); \
        RETURN_##type##_BOTH = RETURN_##type##_##CO##; \
        __if_exists( RETURN_##type##B_##CO## ) \
        { \
            RETURN_##type##B_BOTH = RETURN_##type##B_##CO##; \
        } \
        __if_exists( RETURN_##type##C_##CO## ) \
        { \
            RETURN_##type##C_BOTH = RETURN_##type##C_##CO##; \
        }

// Check original byte before hooking
#define EZHookInstallChecked(type) \
        __if_not_exists( RETURN_##type##_US ) \
        { \
            HookCheckOriginalByte( HOOKPOS_##type, HOOKCHECK_##type ); \
        } \
        __if_exists( RETURN_##type##_US ) \
        { \
            if ( pGameInterface->GetGameVersion () == VERSION_US_10 ) \
            { \
                HookCheckOriginalByte( HOOKPOS_##type##_US, HOOKCHECK_##type##_US ); \
            } \
            else \
            { \
                HookCheckOriginalByte( HOOKPOS_##type##_EU, HOOKCHECK_##type##_EU ); \
            } \
        } \
        EZHookInstall( type )

//bool IsSlowMem(const void* pAddr, uint uiAmount);
BOOL HookInstall(DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize);
BYTE* CreateJump(DWORD dwFrom, DWORD dwTo, BYTE* ByteArray);
bool memcpy_safe(void *dest, const void *src, uint32_t len, int check = NULL, const void *checkdata = NULL);
bool memcmp_safe(const void *_s1, const void *_s2, uint32_t len);
uint8_t* hex_to_bin(const char* str);
bool isBadPtr_readAny(void *pointer, ULONG size);
bool isBadPtr_writeAny(void *pointer, ULONG size);

class Memory
{
private:
	static DWORD memoryProtectedDump;

public:
	template<class T, class U> static void PutSingle(U pMemory, T value);
	template <class T, class U> static void InstallJmp(T address, U proxy, DWORD& jumpback, DWORD dwLen, DWORD jumpbackPos = NULL);
	template <class T, class U> static void InstallJmp(T address, U proxy, DWORD dwLen = 5);
	template <class T>
	static inline BOOL unprotectMemory(T address, SIZE_T size, DWORD* out = NULL)
	{
		return VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, (out != NULL) ? out : &memoryProtectedDump);
	}
	static inline void memCopy(void* ptr, const void* src, int length) { memcpy(ptr, src, length); }
	static inline void memSet(void* ptr, int value, int amount) { memset(ptr, value, amount); }
	template <class T, class U>
	static inline void memPut(U ptr, const T value, int size = sizeof(T))
	{
		void* pointer = reinterpret_cast<void*>(ptr);

		if (*(static_cast<T*>(pointer)) != value)
			memcpy(pointer, &value, size);
	}
	static inline void memCopyFast(void* ptr, const void* src, int length) { memcpy(ptr, src, length); }
	static inline void memSetFast(void* ptr, int value, int amount) { memset(ptr, value, amount); }
	template <class T, class U>
	static inline void memPutFast(U ptr, const T value) { *(T*)ptr = value; }

	static void ApplyJmp(BYTE* pAddress, DWORD dwProxy, DWORD dwLen);
};

template <class T, class U>
void Memory::InstallJmp(T address, U proxy, DWORD& jumpback, DWORD dwLen, DWORD jumpbackPos)
{
	if (!jumpbackPos)
		jumpbackPos = dwLen;

	jumpback = (DWORD)address + jumpbackPos;
	ApplyJmp((BYTE*)address, (DWORD)proxy, dwLen);
}

template <class T, class U>
static void Memory::InstallJmp(T address, U proxy, DWORD dwLen)
{
	return ApplyJmp((BYTE*)address, (DWORD)proxy, dwLen);
}

template<class T, class U>
void Memory::PutSingle(U pMemory, T value)
{
	*(T*)pMemory = value;
}
