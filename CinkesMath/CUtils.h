#pragma once
#include "CScalar.h"
#include <cmath>

#include "CVector3.h"

//Group: CMath
/*ClassDescription: Utility class for easy switching between floatand double precision
*/
namespace Cinkes
{
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
		static CScalar Atan2(CScalar a_First, CScalar a_Second) { std::atan2(a_First, a_Second); }
		static CScalar Sqrt(CScalar a_Value) { return sqrt(a_Value); }
		static CScalar Abs(CScalar a_Value) { return abs(a_Value); }
		static CScalar Deg2Rad(CScalar a_Degrees) { return a_Degrees / 57.2957795; }
		static CScalar Rad2Deg(CScalar a_Radians) { return a_Radians * 57.2957795; }
		static CScalar Sgn(CScalar a_Magnitude, CScalar a_Number) { return std::copysign(a_Magnitude, a_Number); }
		static CScalar Pow(CScalar a_Number, CScalar a_Power) { return pow(a_Number, a_Power); }
#else
		static CScalar Cos(CScalar a_Value) { return std::cosf(a_Value); }
		static CScalar Acos(CScalar a_Value) { return std::acosf(a_Value); }
		static CScalar Sin(CScalar a_Value) { return std::sinf(a_Value); }
		static CScalar Asin(CScalar a_Value) { return std::asinf(a_Value); }
		static CScalar Tan(CScalar a_Value) { return std::tanf(a_Value); }
		static CScalar Atan(CScalar a_Value) { return std::atanf(a_Value); }
		static CScalar Atan2(CScalar a_First, CScalar a_Second) { return std::atan2f(a_First, a_Second); }
		static CScalar Sqrt(CScalar a_Value) { return sqrtf(a_Value); }
		static CScalar Abs(CScalar a_Value) { return fabs(a_Value); }
		static CScalar Deg2Rad(CScalar a_Degrees) { return a_Degrees / 57.2957795f; }
		static CScalar Rad2Deg(CScalar a_Radians) { return a_Radians * 57.2957795f; }
		static CScalar Sgn(CScalar a_Magnitude, CScalar a_Number) { return std::copysignf(a_Magnitude, a_Number); }
		static CScalar Pow(CScalar a_Number, CScalar a_Power) { return powf(a_Number, a_Power); }

#endif
	};
}
