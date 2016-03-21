#ifndef __MidiSequencer__axAudioUtils__
#define __MidiSequencer__axAudioUtils__

#include <iostream>

#include <cmath>

struct axOuputStereo {
	float left, right;
};

namespace ax {
namespace Audio {
	int SecondeToSample(const double& seconde, const int& samplingRate);

	template <typename T>
	T LineairInterpole(const T& y1, const T& y2, const T& mu)
	{
		return y1 + mu * (y2 - y1);
	}

	template <typename T>
	T LogarithmicInterpole(const T& y1, const T& y2, const T& mu)
	{
		return pow(y2, mu) * pow(y1, 1.0 - mu);
	}

	template <typename T> T Clamp(T d, T min, T max)
	{
		const T t = d < min ? min : d;
		return t > max ? max : t;
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

#endif /* defined(__MidiSequencer__axAudioUtils__) */
