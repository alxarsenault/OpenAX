#ifndef __AX_AUDIO_FILTER__
#define __AX_AUDIO_FILTER__

#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <vector>
#include <string>
//#include <random>
//#include <fstream>
//#include "axUtils.h"
//#include "axC++.h"

//#include "portaudio.h"

#ifndef TWOPI
#define TWOPI (6.2831853071795864)
#endif

#ifndef ST_RATIO
#define ST_RATIO (1.0594630943592952)
#endif

#define CLIP(x, min, max)                                                      \
	if (x > max) {                                                             \
		x = max;                                                               \
	}                                                                          \
	if (x < min) {                                                             \
		x = min;                                                               \
	}
#define MIN(x, min)                                                            \
	if (x < min)                                                               \
		x = min;
#define MAX(x, max)                                                            \
	if (x > max)                                                               \
		x = max;

enum axAudioFilterType {
	axAUDIO_FILTER_LPF,
	axAUDIO_FILTER_HPF,
	axAUDIO_FILTER_BPF,
	axAUDIO_FILTER_NOTCH,
	axAUDIO_FILTER_PEAK,
	axAUDIO_FILTER_LOW_SHELF,
	axAUDIO_FILTER_HIGH_SHELF
};

struct axAudioStereoOutput {
	float left, right;
};

struct t_out // STEREO
	{
	t_out()
	{
	}

	t_out(const float& left, const float& right)
		: l(left)
		, r(right)
	{
	}

	float l, r;
};

//-----------------------------------------------------------------------------
//  Audio_Filter
//-----------------------------------------------------------------------------
class axAudioFilter {
public:
	axAudioFilter();
	float Process(float in);

	void ProcessMonoBlock(float* out, unsigned long frameCount);
	void ProcessStereoBlock(float* out, unsigned long frameCount);

	t_out ProcessStereo(t_out in);
	void ProcessStereo(float* in, float* out);

	void SetFreq(float f);
	void SetQ(float f);
	void SetGain(float f);

	float GetFreq() const;
	float GetQ() const;
	float GetGain() const;

	void SetFreqEnvelopePtr(float* ptr);
	void SetFreqEnvelopeAmountPtr(float* ptr);

	float* lfo[2];
	float* lfoAmnt[2];

	float* env[2]; // 0 : Frequency envelope, 1 : Q envelope.
	float* envAmnt[2]; // 0 : Freq env amount, 1 : Q env amount.

	// private:
	float freq, q, gain;
	void Compute_Variables(float freq, float q);
	void Biquad_Coeff(int fType);
	float b0, b1, b2, a0, a1, a2;
	float x1, x2, y1, y2;
	float rx1, rx2, ry1, ry2;
	float c, w0, alpha;
	int filterType;
	bool init;
	long sr;
};

#endif // __AX_AUDIO_FILTER__