#include "StdInc.h"

#include "CDirect3DEvents9.h"

void CDirect3DEvents9::OnPresent(IDirect3DDevice9* pDevice)
{
	static bool bDoneReset = false;
	if (!bDoneReset)
	{
		bDoneReset = true;
		for (uint i = 0; i < 16; i++)
		{
			pDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			pDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			pDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		}
	}

	Core::GetSingleton().onPostFramePulse();
}