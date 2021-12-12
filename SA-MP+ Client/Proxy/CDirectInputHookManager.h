#pragma once

#include "CDirectInputHook8.h"

class CDirectInputHookManager
{
private:
	CDirectInputHook8* directInputHook8;

public:
	CDirectInputHookManager();
	~CDirectInputHookManager();

	void applyHook();
	void removeHook();
};
