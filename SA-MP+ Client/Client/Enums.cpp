#include "StdInc.h"

#include "Enums.h"

IMPLEMENT_ENUM_BEGIN(eEulerRotationOrder)
ADD_ENUM(EULER_DEFAULT, "default")
ADD_ENUM(EULER_ZXY, "ZXY")
ADD_ENUM(EULER_ZYX, "ZYX")
ADD_ENUM(EULER_MINUS_ZYX, "MINUS_ZYX")
IMPLEMENT_ENUM_END("rotation-order")
