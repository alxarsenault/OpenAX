#ifndef __AX_AUDIO_FIRST_ORDER_FILTER__
#define __AX_AUDIO_FIRST_ORDER_FILTER__

#include "AudioUtils.h"
#include "Utils.h"

namespace ax {
namespace Audio {
	// T Type of input ouput buffers.
	// P Type of processing variables.
	template <typename T = double, typename P = double> class FirstOrderFilter {
	public:
		enum Type { Lowpass, Highpass };

		FirstOrderFilter(const unsigned long& sampling_rate,
			const Type& type = Lowpass, const P& freq = 20000.0)
			: _samplingRate(sampling_rate)
			, _type(type)
			, _freq(freq)
			, _active(true)
			, _needToInit(true)
		{
			ComputeCoefficients();
		}

		void SetSamplingRate(const unsigned long& sr)
		{
			_samplingRate = sr;
			ComputeCoefficients();
		}

		void SetFilterType(const Type& type)
		{
			_type = type;
			ComputeCoefficients();
		}

		void SetFreq(const P& freq)
		{
			_freq = freq;
			ComputeCoefficients();
		}

		void SetActive(const bool& active)
		{
			_active = active;
		}

		void ProcessMonoSample(T* sample)
		{
			if (_active) {
				if (_needToInit) {
					_past = *sample;
					_needToInit = false;
				}

				P before = *sample;
				P after = _a * before - _b * _past;
				*sample = after;
				_past = after;
			}
		}

		void ProcessMonoBlock(T** output, const unsigned long& frameCount)
		{
			if (_active) {
				P before = 0.0, after = 0.0;
				T* mono_out = output[0];

				P past = _past;
				P a = _a, b = _b;

				if (_needToInit) {
					past = *mono_out;
					_needToInit = false;
				}

				for (unsigned long i = 0; i < frameCount; i++) {

					before = *mono_out;

					after = a * before - b * past;

					*mono_out++ = after;

					past = after;
				}

				_past = past;
			}
		}

		void ProcessStereoBlock(T** output, const unsigned long& frameCount)
		{
			if (_active) {
				P before_left = 0.0, before_right = 0.0;
				P after_left = 0.0, after_right = 0.0;
				T *left = output[0], *right = output[1];

				P past = _past, rpast = _rpast;
				P a = _a, b = _b;

				if (_needToInit) {
					past = *left;
					rpast = *right;
					_needToInit = false;
				}

				for (unsigned long i = 0; i < frameCount; i++) {

					before_left = *left;
					before_right = *right;

					after_left = a * before_left - b * past;
					after_right = a * before_right - b * rpast;

					*left++ = after_left;
					*right++ = after_right;

					past = after_left;
					rpast = after_right;
				}

				_past = past;
				_rpast = rpast;
			}
		}

	private:
		P _a, _b;
		P _past, _rpast;
		P _freq;
		Type _type;
		bool _active, _needToInit;
		unsigned long _samplingRate;

		void ComputeCoefficients()
		{
			_freq = ax::Utils::Clamp<P>(_freq, P(1.0), P(_samplingRate * 0.5));

			P w0 = ax::audio::TwoPi * _freq / double(_samplingRate);
			P cosW0 = cos(w0);

			switch (_type) {
			case Lowpass:
				_b = sqrt(pow(2.0 - cosW0, 2.0) - 1.0) - 2.0 + cosW0;
				_a = 1.0 + _b;
				break;

			case Highpass:
				_b = 2.0 - cosW0 - sqrt(pow(2.0 - cosW0, 2.0) - 1.0);
				_a = 1.0 - _b;
				break;
			}
		}
	};
}
}

#endif // __AX_AUDIO_FIRST_ORDER_FILTER__