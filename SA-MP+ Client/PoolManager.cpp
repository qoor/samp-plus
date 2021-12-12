#include "StdInc.h"

#include "PoolManager.h"
#include <Detours/detours.h>
#include <game_sa/CVehicleSA.h>

CPools* PoolManager::pool = NULL;

void PoolManager::initialize()
{
	pool = core->getGame()->GetPools();

	initHandlers();
	initHooks();
}

void PoolManager::initHandlers()
{
	core->getMultiplayer()->SetGameVehicleDestructHandler(PoolManager::CVehicleDestructorHandler);
	core->getMultiplayer()->SetGamePlayerDestructHandler(PoolManager::CPedDestructorHandler);
}

void PoolManager::CVehicleDestructorHandler(CEntitySAInterface* vehicle)
{
	if (vehicle == NULL)
		return;

	Debug::write("+ CVehicle* ~CVehicle()");
	CVehicle* targetVehicle = pool->GetVehicle(reinterpret_cast<DWORD*>(vehicle));

	//if (targetVehicle != NULL)
		pool->RemoveVehicle(targetVehicle, false);

	Debug::write("- CVehicle* ~CVehicle()");
}

void PoolManager::CPedDestructorHandler(CEntitySAInterface* ped)
{
	if (ped == NULL)
		return;

	Debug::write("+ CPed* ~CPed()");
	CPed* targetPed = pool->GetPed(reinterpret_cast<DWORD*>(ped));

	//if (targetPed != NULL)
		pool->RemovePed(targetPed, false);

	Debug::write("- CPed* ~CPed()");
}

void _cdecl CVehicle_constructor(CVehicleSAInterface* vehicle) // 인터페이스에는 아무 데이터가 들어있지 않음을 주의.
{
	if (vehicle == NULL)
		return;

	Debug::write("+ CVehicle* CVehicle()");
	/*CVehicle* vehicleValid = core->getGame()->GetPools()->GetVehicle((DWORD*)vehicle);
	
	// create & add new CVehicle to CPools
	if (vehicleValid == NULL)*/
		core->getGame()->GetPools()->AddVehicle((DWORD*)vehicle);

	Debug::write("- CVehicle* CVehicle()");
}

#define HOOKPOS_CVehicle_constructor	0x6D6259
DWORD	RETURN_CVehicle_constructor = 0x6D6263;
void _declspec (naked) HOOK_CVehicle_constructor()
{
	__asm
	{
		// perform over-written asm
		mov fs : 0, ecx
		add esp, 0x10

		// call handler
		push eax
		call CVehicle_constructor
		add esp, 0x4

		// return
		jmp RETURN_CVehicle_constructor
	}
}

// ---------------------------------------------------
void _cdecl CPed_constructor(CPedSAInterface* ped)
{
	if (ped == NULL)
		return;

	Debug::write("+ CPed* CPed()");
	/*DWORD* pedId = reinterpret_cast<DWORD*>(ped);
	CPed* pedValid = core->getGame()->GetPools()->GetPed(pedId);

	// create & add new CPed to CPools
	if (pedValid == NULL)*/
		core->getGame()->GetPools()->AddPed((DWORD*)ped);

	Debug::write("- CPed* CPed()");

	// use this if the player ped ever becomes deleted, this will reset the pointer
	// this only works if there's no other peds since the pool will resize automatically
	//if ( pPools->GetPedRef( pPools->AddPed( (DWORD *)ped ) ) == CPOOLS_PED_SELF_REF )
	//	pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
}

#define HOOKPOS_CPed_constructor	0x5E8606
DWORD	RETURN_CPed_constructor = 0x5E8610;
void _declspec (naked) HOOK_CPed_constructor()
{
	__asm
	{
		// perform over-written asm
		mov fs : 0, ecx
		add esp, 0x28

		// call handler
		push eax
		call CPed_constructor

		//pop eax
		add esp, 0x4

		// return
		jmp RETURN_CPed_constructor
	}
}

void PoolManager::initHooks()
{
	HookInstall(HOOKPOS_CVehicle_constructor, (DWORD)HOOK_CVehicle_constructor, 6);
	//HookInstall(HOOKPOS_CVehicle_destructor, (DWORD)HOOK_CVehicle_destructor, 6);
	HookInstall(HOOKPOS_CPed_constructor, (DWORD)HOOK_CPed_constructor, 6);
	//HookInstall(HOOKPOS_CPed_destructor, (DWORD)HOOK_CPed_destructor, 6);
}
