#include "axAudioFilter.h"
#include "AudioUtils.h"
#include "Utils.h"

axAudioFilter::axAudioFilter()
{
	sr = 44100;
	filterType = axAUDIO_FILTER_LPF;
	init = true;
	freq = 20000;
	q = 0.707;
	gain = 1.0;

	// SET_NULL_PTR(lfo, 2);
	// SET_NULL_PTR(lfoAmnt, 2);
	lfoAmnt[0] = nullptr;
	lfoAmnt[1] = nullptr;
	// SET_NULL_PTR(env, 2);
	// SET_NULL_PTR(envAmnt, 2);
	envAmnt[0] = nullptr;
	envAmnt[1] = nullptr;

	Compute_Variables(freq, q);
}
void axAudioFilter::SetFreq(float f)
{
	freq = ax::Utils::Clamp<float>(f, 20.0, 20000.0);
	Compute_Variables(freq, q);

//	std::cout << "filter freq : " << freq << std::endl;
}
void axAudioFilter::SetQ(float f)
{
	q = ax::Utils::Clamp<float>(f, 0.01, 50.0);
	Compute_Variables(freq, q);
}

void axAudioFilter::SetGain(float f)
{
	gain = ax::Utils::Clamp<float>(f, 0.0, 3.0);

//	std::cout << "filter gain : " << gain << std::endl;
}

float axAudioFilter::GetFreq() const
{
	return freq;
}
float axAudioFilter::GetQ() const
{
	return q;
}
float axAudioFilter::GetGain() const
{
	return gain;
}

void axAudioFilter::SetFreqEnvelopePtr(float* ptr)
{
	env[0] = ptr;
	// if(env[0] != nullptr)
	// {
	// 	cout << "ENV[0] diff from nullptr" << endl;
	// }
}

void axAudioFilter::SetFreqEnvelopeAmountPtr(float* ptr)
{
	envAmnt[0] = ptr;

	// if(envAmnt[0] != nullptr)
	// {
	// 	cout << "ENV[0] diff from nullptr" << endl;
	// }
}

// void SetFreqEnvelopePtr(float* ptr);
// void SetFreqEnvelopeAmountPtr(float* ptr);

float axAudioFilter::Process(float in)
{
	float v;
	float f = freq;
	float res = q;
	bool compute_coeff = false;
	// Compute_Variables(float freq, float q)

	if (init) {
		x1 = x2 = y1 = y2 = in;
		init = false;
	}

	if (env[0] != nullptr && envAmnt[0] != nullptr) {
		// cout << "ENV FREQ" << endl;
		float modEnvFreq = *env[0];
		f = f + (288 * *envAmnt[0] * modEnvFreq * (f * (ST_RATIO - 1.0) + 1.0));
		CLIP(f, 20, 20000);
		compute_coeff = true;
	}

	if (compute_coeff) {
		Compute_Variables(f, res);
	}
	// C
	v = ((b0 * in) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2)) / a0;

	y2 = y1;
	y1 = v;
	x2 = x1;
	x1 = in;

	return v * gain;
}

void axAudioFilter::ProcessMonoBlock(float* out, unsigned long frameCount)
{
	double before_value = 0.0;

	if (init) {
		x1 = x2 = y1 = y2 = *out;
		init = false;
	}

	for (int i = 0; i < frameCount; i++) {
		before_value = *out;
		double after_process = ((b0 * before_value) + (b1 * x1) + (b2 * x2)
								   - (a1 * y1) - (a2 * y2)) / a0;
		*out++ = after_process * gain;

		y2 = y1;
		y1 = after_process;
		x2 = x1;
		x1 = before_value;
	}
}

void axAudioFilter::ProcessStereoBlock(float* out, unsigned long frameCount)
{
	double before_value = 0.0;
	double f = freq;
	bool needComputeCoefficients = false;

	if (env[0] != nullptr && envAmnt[0] != nullptr) {
		//        cout << "ENV FREQ" << endl;
		float modEnvFreq = *env[0];
		f = f + (288 * *envAmnt[0] * modEnvFreq * (f * (ST_RATIO - 1.0) + 1.0));
		f = ax::Utils::Clamp<double>(f, 20.0, 20000.0);
		needComputeCoefficients = true;
	}

	if (needComputeCoefficients) {
		Compute_Variables(f, q);
	}

	if (init) {
		x1 = x2 = y1 = y2 = *out;
		init = false;
	}

	for (int i = 0; i < frameCount; i++) {
		before_value = *out;
		double after_process = ((b0 * before_value) + (b1 * x1) + (b2 * x2)
								   - (a1 * y1) - (a2 * y2)) / a0;

		double v = after_process * gain;
		*out++ = v;
		*out++ = v;

		y2 = y1;
		y1 = after_process;
		x2 = x1;
		x1 = before_value;
	}
}

t_out axAudioFilter::ProcessStereo(t_out in)
{
	t_out v;
	float f = freq;
	float r = q;
	bool comp = true;

	//	//LFO FREQ
	//--------------------------------------------------------------------
	//	if (lfo[0] != NULL && lfoAmnt[0] != NULL)
	//	{
	//		float modLfoFreq = *lfo[0];
	//		//288 = 12 demiton * 12 * 2
	//		f = f + (288 * *lfoAmnt[0] * modLfoFreq * (f * (ST_RATIO - 1.0) +
	//1.0));
	//		CLIP(f, 20, 20000);
	//		comp = 1;
	//	}
	// ENV FREQ
	//	if (env[0] != nullptr && envAmnt[0] != nullptr)
	//	{
	////		cout << "ENV FREQ" << endl;
	//		float modEnvFreq = *env[0];
	//        float freqModAdd = (288 * *envAmnt[0] * modEnvFreq * (f *
	//        (ST_RATIO - 1.0) + 1.0));
	////        cout << "ENV FREQ : " << freqModAdd << endl;
	//		f = f + freqModAdd;
	//		CLIP(f, 20, 20000);
	//		comp = 1;
	//	}
	////---------------------------------------------------------------------------

	// LFO RES
	// ---------------------------------------------------------------------
	//	if (lfo[1] != NULL && lfoAmnt[1] != NULL)
	//	{
	//		float modLfoRes = *lfo[1];
	//		r = r + (*lfoAmnt[1] * modLfoRes * 10.0);
	//		CLIP(r, 0.01, 10);
	//		comp = 1;
	//	}
	// ENV RES
	//	if (env[1] != NULL && envAmnt[1] != NULL)
	//	{
	//		float modEnvRes = *env[1];
	//		r = r + (*envAmnt[1] * modEnvRes * 10.0);
	//		CLIP(r, 0.01, 10);
	//		comp = 1;
	//	}//---------------------------------------------------------------------------

	if (comp)
		Compute_Variables(f, r);

	if (init) {
		x1 = x2 = y1 = y2 = in.l;
		rx1 = rx2 = ry1 = ry2 = in.r;
		init = false;
	}

	if (a0 == 0.0) {
//		std::cout << "a0 is 0.0" << std::endl;
	}

	// Compute_Variables(in, float q)
	v.l = ((b0 * in.l) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2)) / a0;
	v.r = ((b0 * in.r) + (b1 * rx1) + (b2 * rx2) - (a1 * ry1) - (a2 * ry2)) / a0;

	y2 = y1;
	y1 = v.l;
	x2 = x1;
	x1 = in.l;

	ry2 = ry1;
	ry1 = v.r;
	rx2 = rx1;
	rx1 = in.r;

	v.l *= gain;
	v.r *= gain;

	//	return v;
	return in;
}

void axAudioFilter::ProcessStereo(float* in, float* out)
{
	//    t_out v;
	float f = freq;
	float r = q;
	bool comp = true;

	float out_value[2] = { 0.0, 0.0 };

	//	//LFO FREQ
	//--------------------------------------------------------------------
	//	if (lfo[0] != NULL && lfoAmnt[0] != NULL)
	//	{
	//		float modLfoFreq = *lfo[0];
	//		//288 = 12 demiton * 12 * 2
	//		f = f + (288 * *lfoAmnt[0] * modLfoFreq * (f * (ST_RATIO - 1.0) +
	//1.0));
	//		CLIP(f, 20, 20000);
	//		comp = 1;
	//	}
	// ENV FREQ
	//	if (env[0] != nullptr && envAmnt[0] != nullptr)
	//	{
	////		cout << "ENV FREQ" << endl;
	//		float modEnvFreq = *env[0];
	//        float freqModAdd = (288 * *envAmnt[0] * modEnvFreq * (f *
	//        (ST_RATIO - 1.0) + 1.0));
	////        cout << "ENV FREQ : " << freqModAdd << endl;
	//		f = f + freqModAdd;
	//		CLIP(f, 20, 20000);
	//		comp = 1;
	//	}
	////---------------------------------------------------------------------------

	// LFO RES
	// ---------------------------------------------------------------------
	//	if (lfo[1] != NULL && lfoAmnt[1] != NULL)
	//	{
	//		float modLfoRes = *lfo[1];
	//		r = r + (*lfoAmnt[1] * modLfoRes * 10.0);
	//		CLIP(r, 0.01, 10);
	//		comp = 1;
	//	}
	// ENV RES
	//	if (env[1] != NULL && envAmnt[1] != NULL)
	//	{
	//		float modEnvRes = *env[1];
	//		r = r + (*envAmnt[1] * modEnvRes * 10.0);
	//		CLIP(r, 0.01, 10);
	//		comp = 1;
	//	}//---------------------------------------------------------------------------

	if (comp)
		Compute_Variables(f, r);

	if (init) {
		x1 = x2 = y1 = y2 = in[0];
		rx1 = rx2 = ry1 = ry2 = in[1];
		init = false;
	}

	if (a0 == 0.0) {
//		std::cout << "a0 is 0.0" << std::endl;
	}

	// Compute_Variables(in, float q)
	out_value[0] = ((b0 * in[0]) + (b1 * x1) + (b2 * x2) - (a1 * y1) - (a2 * y2)) / a0;
	out_value[1] = ((b0 * in[1]) + (b1 * rx1) + (b2 * rx2) - (a1 * ry1) - (a2 * ry2)) / a0;

	y2 = y1;
	y1 = out_value[0];
	x2 = x1;
	x1 = in[0];

	ry2 = ry1;
	ry1 = out_value[1];
	rx2 = rx1;
	rx1 = in[1];

	out_value[0] *= gain;
	out_value[1] *= gain;

	out[0] += out_value[0];
	out[1] += out_value[1];
}

void axAudioFilter::Compute_Variables(float ff, float qq)
{
	MIN(ff, 1);
	MAX(ff, 44100.0 * 0.5);

	MIN(qq, 0.1);
	MAX(qq, 100);

	w0 = TWOPI * ff / double(sr);
	c = cosf(w0);
	alpha = sinf(w0) / (2.0 * qq);

	Biquad_Coeff(filterType);
}
void axAudioFilter::Biquad_Coeff(int fType)
{
	switch (fType) {
	case axAUDIO_FILTER_LPF:
		b0 = b2 = (1 - c) / 2;
		b1 = 1 - c;
		a0 = 1 + alpha;
		a1 = -2 * c;
		a2 = 1 - alpha;
		break;

	case axAUDIO_FILTER_HPF:
		b0 = (1 + c) / 2;
		b1 = -(1 + c);
		b2 = b0;
		a0 = 1 + alpha;
		a1 = -2 * c;
		a2 = 1 - alpha;
		break;

	case axAUDIO_FILTER_BPF:
		b0 = alpha;
		b1 = 0;
		b2 = -alpha;
		a0 = 1 + alpha;
		a1 = -2 * c;
		a2 = 1 - alpha;
		break;
	}
}