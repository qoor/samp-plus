#pragma once

class PoolManager
{
private:
	static CPools* pool;

public:
	static void initialize();
	static void initHandlers();
	static void initHooks();

	//CPools* getPool() { return pool; }

	static void CVehicleDestructorHandler(CEntitySAInterface* vehicle);
	static void CPedDestructorHandler(CEntitySAInterface* ped);
};
