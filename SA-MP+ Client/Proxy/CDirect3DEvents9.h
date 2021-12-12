#pragma once

#include <DirectX/d3d9.h>

class CDirect3DEvents9
{
public:
	static void OnPresent(IDirect3DDevice9* pDevice);
};
