#pragma once
#include "CScalar.h"
#include <cmath>
class CUtils
{
public:
#if USE_DOUBLE == true
	static CScalar Cos(CScalar a_Value) { return std::cos(a_Value); }
	static CScalar Acos(CScalar a_Value) { return std::acos(a_Value); }
	static CScalar Sin(CScalar a_Value) { return std::sin(a_Value); }
	static CScalar Asin(CScalar a_Value) { return std::asin(a_Value); }
	static CScalar Tan(CScalar a_Value) { return std::tan(a_Value); }
	static CScalar Atan(CScalar a_Value) { return std::atan(a_Value); }
	static CScalar Sqrt(CScalar a_Value) { return sqrt(a_Value); }
	static CScalar Atan2(CScalar a_Y, CScalar a_X) { return std::atan2(a_Y, a_X); }
	static CScalar Abs(CScalar a_Value) { return abs(a_Value); }
#else
	static CScalar Cos(CScalar a_Value) { return std::cosf(a_Value); }
	static CScalar Acos(CScalar a_Value) { return std::acosf(a_Value); }
	static CScalar Sin(CScalar a_Value) { return std::sinf(a_Value); }
	static CScalar Asin(CScalar a_Value) { return std::asinf(a_Value); }
	static CScalar Tan(CScalar a_Value) { return std::tanf(a_Value); }
	static CScalar Atan(CScalar a_Value) { return std::atanf(a_Value); }
	static CScalar Sqrt(CScalar a_Value) { return sqrtf(a_Value); }
	static CScalar Atan2(CScalar a_Y, CScalar a_X) { return std::atan2f(a_Y, a_X); }
	static CScalar Abs(CScalar a_Value) { return fabs(a_Value); }

#endif
};

