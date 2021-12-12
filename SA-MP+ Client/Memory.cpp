#include "StdInc.h"

#include "Memory.h"

#define MAX_JUMPCODE_SIZE 50

DWORD Memory::memoryProtectedDump = 0;

/*bool IsSlowMem(const void* pAddr, uint uiAmount)
{
	DWORD uiAddr = ((DWORD)pAddr) >> 8;
	DWORD uiAddrLast = (((DWORD)pAddr) + uiAmount - 1) >> 8;

	for (; uiAddr <= uiAddrLast; uiAddr++)
	{
		if (uiAddr < 0x4010 || uiAddr > 0x8A40 || uiAddr == 0x4C03 || uiAddr == 0x4EB9 || uiAddr == 0x5022 || uiAddr == 0x5023 || uiAddr == 0x50AB ||
			uiAddr == 0x50BF || uiAddr == 0x5332 || uiAddr == 0x609C || uiAddr == 0x60D8 || uiAddr == 0x60F2 || uiAddr == 0x6420 || uiAddr == 0x648A ||
			uiAddr == 0x64CA || uiAddr == 0x6870 || uiAddr == 0x6A07 || uiAddr == 0x6AEA || uiAddr == 0x729B || uiAddr == 0x742B)
			return false;
	}
	return true;
}*/

BOOL HookInstall(DWORD dwInstallAddress, DWORD dwHookHandler, int iJmpCodeSize)
{
	BYTE JumpBytes[MAX_JUMPCODE_SIZE];
	Memory::memSetFast(JumpBytes, 0x90, MAX_JUMPCODE_SIZE);

	if (CreateJump(dwInstallAddress, dwHookHandler, JumpBytes))
	{
		if (IsSlowMem((PVOID)dwInstallAddress, iJmpCodeSize))
			Memory::memCopy((PVOID)dwInstallAddress, JumpBytes, iJmpCodeSize);
		else
			Memory::memCopyFast((PVOID)dwInstallAddress, JumpBytes, iJmpCodeSize);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BYTE* CreateJump(DWORD dwFrom, DWORD dwTo, BYTE* ByteArray)
{
	ByteArray[0] = 0xE9;
	Memory::memPutFast<DWORD>(&ByteArray[1], dwTo - (dwFrom + 5));

	return ByteArray;
}

void Memory::ApplyJmp(BYTE* pAddress, DWORD dwProxy, DWORD dwLen)
{
	DWORD dwOld, dwRelAddr;

	unprotectMemory(pAddress, dwLen, &dwOld);
	dwRelAddr = (DWORD)(dwProxy - (DWORD)pAddress) - 5;

	*pAddress = ASM_JMP;
	PutSingle<DWORD>(pAddress + 1, dwRelAddr);

	for (unsigned long i = 5; i < dwLen; ++i)
		PutSingle<BYTE>(pAddress + i, ASM_NOP);

	VirtualProtect((void*)pAddress, dwLen, dwOld, &memoryProtectedDump);
}

bool isBadPtr_handlerAny(void *pointer, ULONG size, DWORD dwFlags)
{
	DWORD						dwSize;
	MEMORY_BASIC_INFORMATION	meminfo;

	if (NULL == pointer)
		return true;

	memset(&meminfo, 0x00, sizeof(meminfo));
	dwSize = VirtualQuery(pointer, &meminfo, sizeof(meminfo));

	if (0 == dwSize)
		return true;

	if (MEM_COMMIT != meminfo.State)
		return true;

	if (0 == (meminfo.Protect & dwFlags))
		return true;

	if (size > meminfo.RegionSize)
		return true;

	if ((unsigned)((char *)pointer - (char *)meminfo.BaseAddress) > (unsigned)(meminfo.RegionSize - size))
		return true;

	return false;
}

bool isBadPtr_readAny(void *pointer, ULONG size)
{
	return isBadPtr_handlerAny(pointer, size, PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
		PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
}

bool isBadPtr_writeAny(void *pointer, ULONG size)
{
	return isBadPtr_handlerAny(pointer, size,
		PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
}

static int __page_size_get(void)
{
	static int	page_size = -1;
	SYSTEM_INFO si;

	if (page_size == -1)
	{
		GetSystemInfo(&si);
		page_size = (int)si.dwPageSize;
	}

	return page_size;
}

static int __page_write(void *_dest, const void *_src, uint32_t len)
{
	static int		page_size = __page_size_get();
	uint8_t			*dest = (uint8_t *)_dest;
	const uint8_t	*src = (const uint8_t *)_src;
	DWORD			prot_prev = 0;
	int				prot_changed = 0;
	int				ret = 1;

	while (len > 0)
	{
		ret = 1;
		int page_offset = (int)((UINT_PTR)dest % page_size);
		int page_remain = page_size - page_offset;
		int this_len = len;

		if (this_len > page_remain)
			this_len = page_remain;

		if (isBadPtr_writeAny(dest, this_len))
		{
			if (!VirtualProtect((void *)dest, this_len, PAGE_EXECUTE_READWRITE, &prot_prev))
				ret = 0;
			else
				prot_changed = 1;
		}

		if (ret)
			memcpy(dest, src, this_len);

		if (prot_changed)
		{
			DWORD	dummy;

			if (!VirtualProtect((void *)dest, this_len, prot_prev, &dummy))
				Debug::write("__page_write() could not restore original permissions for ptr %p", dest);
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

static int __page_read(void *_dest, const void *_src, uint32_t len)
{
	static int	page_size = __page_size_get();
	uint8_t		*dest = (uint8_t *)_dest;
	uint8_t		*src = (uint8_t *)_src;
	DWORD		prot_prev = 0;
	int			prot_changed = 0;
	int			ret = 1;

	while (len > 0)
	{
		ret = 1;
		int page_offset = (int)((UINT_PTR)src % page_size);
		int page_remain = page_size - page_offset;
		int this_len = len;

		if (this_len > page_remain)
			this_len = page_remain;

		if (isBadPtr_readAny(src, this_len))
		{
			if (!VirtualProtect((void *)src, this_len, PAGE_EXECUTE_READWRITE, &prot_prev))
				ret = 0;
			else
				prot_changed = 1;
		}

		if (ret)
			memcpy(dest, src, this_len);
		else
			memset(dest, 0, this_len);

		if (prot_changed)
		{
			DWORD	dummy;

			if (!VirtualProtect((void *)src, this_len, prot_prev, &dummy))
				Debug::write("__page_read() could not restore original permissions for ptr %p", src);
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

bool memcmp_safe(const void*_s1, const void*_s2, uint32_t len)
{
	const uint8_t	*s1 = (const uint8_t *)_s1;
	const uint8_t	*s2 = (const uint8_t *)_s2;
	uint8_t			buf[4096];

	for (;; )
	{
		if (len > 4096)
		{
			if (!memcpy_safe(buf, s1, 4096) || memcmp(buf, s2, 4096))
				return 0;

			s1 += 4096;
			s2 += 4096;
			len -= 4096;
		}
		else
		{
			if (!memcpy_safe(buf, s1, len) || memcmp(buf, s2, len))
				return false;

			break;
		}
	}

	return true;
}

bool memcpy_safe(void *_dest, const void *_src, uint32_t len, int check, const void *checkdata)
{
	/*static int		page_size = __page_size_get();
	static int		recurse_ok = 1;
	uint8_t			buf[4096];
	uint8_t			*dest = (uint8_t *)_dest;
	const uint8_t	*src = (const uint8_t *)_src;
	bool			ret = true;

	if (check && checkdata)
	{
		if (!memcmp_safe(checkdata, _dest, len))
			return false;
	}

	while (len > 0)
	{
		uint32_t	this_len = sizeof(buf);

		if (this_len > len)
			this_len = len;

		if (!__page_read(buf, src, this_len))
			ret = false;

		if (!__page_write(dest, buf, this_len))
			ret = false;

		len -= this_len;
		src += this_len;
		dest += this_len;
	}

	return ret;*/

	DWORD lastProtected;
	DWORD dummy;

	if (!VirtualProtect(_dest, len, PAGE_EXECUTE_READWRITE, &lastProtected))
	{
		Debug::write("메모리 권한 획득 실패.");

		return false;
	}

	memcpy(_dest, _src, len);

	if (!VirtualProtect(_dest, len, lastProtected, &dummy))
	{
		Debug::write("메모리 권한 복구 실패.");

		return false;
	}

	return true;
}

static signed char hex_to_dec(signed char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	if (ch >= 'a' && ch <= 'f')
		return ch - 'A' + 10;

	return -1;
}

uint8_t* hex_to_bin(const char* str)
{
	int		len = (int)strlen(str);
	uint8_t *buf, *sbuf;

	if (len == 0 || len % 2 != 0)
		return NULL;

	sbuf = buf = (uint8_t *)malloc(len / 2);

	while (*str)
	{
		signed char bh = hex_to_dec(*str++);
		signed char bl = hex_to_dec(*str++);

		if (bl == -1 || bh == -1)
		{
			free(sbuf);
			return NULL;
		}

		*buf++ = (uint8_t)(bl | (bh << 4));
	}

	return sbuf;
}
