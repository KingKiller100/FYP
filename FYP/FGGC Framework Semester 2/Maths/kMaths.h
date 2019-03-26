#pragma once
#define _USE_MATH_DEFINES
#include "Vector3.h"
#include <algorithm>
#include <corecrt_math_defines.h>

typedef  Vector3<int>		Vector3i;
typedef  Vector3<float>		Vector3f;
typedef  Vector3<double>	Vector3d;
typedef  Vector3<unsigned>	Vector3u;

#define TAU (M_PI * 2)

template<class TP>
TP RadiansToDegrees(const TP radians)									{ return radians * std::forward<TP>(360.0 / TAU); }

template<class TP>
TP DegreesToRadians(const TP degrees)									{ return degrees * std::forward<TP>(TAU / 360.f); }

template<class TP>
TP Clamp(const TP value, const TP min, const TP max)					{ return std::forward<TP>(std::min(std::max(value, min), max)); }

template<class TP>
TP AbsClamp(const TP value, const TP min, const TP max)					{ return value >= 0 ? ::Clamp(value, min, max) : -::Clamp(value, min, max); }
