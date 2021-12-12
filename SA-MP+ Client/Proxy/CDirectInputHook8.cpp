#include "StdInc.h"

#include "CDirectInputHook8.h"
#include "CProxyDirectInput8.h"

#include <Detours/detours.h>

template<>
CDirectInputHook8* CSingleton<CDirectInputHook8>::m_pSingleton = NULL;
IDirectInput8* directInput8 = NULL;

CDirectInputHook8::CDirectInputHook8()
{
	directInputCreate = NULL;
	isUnicodeInterface = false;
}

CDirectInputHook8::~CDirectInputHook8()
{

}

bool CDirectInputHook8::applyHook()
{
	char moduleName[] = "DINPUT8.DLL";
	char functionName[] = "DirectInput8Create";

	directInputCreate = reinterpret_cast<pDirectInputCreate>(DetourFunction(DetourFindFunction(moduleName, functionName), reinterpret_cast<PBYTE>(API_DirectInput8Create)));

	return true;
}

bool CDirectInputHook8::removeHook()
{
	if (directInputCreate != NULL)
	{
		DetourRemove(reinterpret_cast<PBYTE>(directInputCreate), reinterpret_cast<PBYTE>(API_DirectInput8Create));

		directInputCreate = NULL;
	}

	return true;
}

HRESULT CDirectInputHook8::API_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	CDirectInputHook8* pThis = CDirectInputHook8::GetSingletonPtr();

	HRESULT hResult = pThis->directInputCreate(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	if (FAILED(hResult))
		return hResult;

	/*if (riidltf == IID_IDirectInputW)
		pThis->isUnicodeInterface = true;
	else*/
		pThis->isUnicodeInterface = false;

	IDirectInput8* pDirectInput8 = static_cast<IDirectInput8*>(*ppvOut);

	CProxyDirectInput8* proxyDirectInput8 = new CProxyDirectInput8(pDirectInput8);
	proxyDirectInput8->AddRef();

	directInput8 = proxyDirectInput8;
	*ppvOut = proxyDirectInput8;

	return hResult;
}