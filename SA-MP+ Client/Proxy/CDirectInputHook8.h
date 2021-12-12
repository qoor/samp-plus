#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <DirectX/dinput.h>
#include <CSingleton.h>

typedef HRESULT(__stdcall* pDirectInputCreate)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

class CDirectInputHook8 : public CSingleton<CDirectInputHook8>
{
private:
	pDirectInputCreate directInputCreate;
	bool isUnicodeInterface;

public:
	CDirectInputHook8();
	~CDirectInputHook8();

	static HRESULT __stdcall API_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

	bool applyHook();
	bool removeHook();
};
