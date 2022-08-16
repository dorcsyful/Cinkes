#pragma once
#include <limits>
#define KILL_DISTANCE 10000
#define USE_MATH_DEFINES
#define USE_DOUBLE false
#if USE_DOUBLE
#define CScalar double
#else
#define CScalar float
#endif

#define CEPSILON std::numeric_limits<float>::epsilon() * 100

 