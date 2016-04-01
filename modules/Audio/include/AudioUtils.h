#ifndef __AUDIO_UTILS_H__
#define __AUDIO_UTILS_H__

#include <iostream>

#include <cmath>

// namespace ax {
// struct axOuputStereo {
//	float left, right;
//};

namespace ax {
namespace audio {
	inline int SecondeToSample(const double& seconde, const int& samplingRate)
	{
		return int(seconde * samplingRate);
	}

	template <typename T> inline T Pow2(T v)
	{
		return v * v;
	}

	const double C0 = 8.175798915643709;
	const double SemiToneRatio = 1.0594630943592952;
	const double InvTwoPi = 0.159154943091895;
	const double TwoPi = 6.2831853071795864;
	const double Pi = 3.141592653589793;
}
}

#endif // __AUDIO_UTILS_H__
