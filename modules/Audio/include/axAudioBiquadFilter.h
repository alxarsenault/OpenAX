#ifndef __AX_AUDIO_BIQUAD_FILTER__
#define __AX_AUDIO_BIQUAD_FILTER__

#include "axAudioUtils.h"

namespace ax {
namespace Audio {
	// T Type of input ouput buffers.
	// P Type of processing variables.
	template <typename T = double, typename P = double> class BiquadFilter {
	public:
		enum Type {
			Lowpass,
			Highpass,
			Bandpass,
			Notch,
			Peak,
			LowShelf,
			HighShelf,
			Allpass
		};

		BiquadFilter(const unsigned long& sampling_rate, const Type& type = Lowpass,
			const P& freq = 20000.0, const P& q = 0.7071067811865476, const P& gain = 1.0)
			: _samplingRate(sampling_rate)
			, _type(type)
			, _freq(freq)
			, _q(q)
			, _gain(gain)
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

		void SetQ(const P& q)
		{
			_q = q;
			ComputeCoefficients();
		}

		void SetGain(const P& gain)
		{
			_gain = gain;
			ComputeCoefficients();
		}

		void SetActive(const bool& active)
		{
			_active = active;
		}

		void ProcessMonoSample(T* sample)
		{
			if (_active) {
				P before = 0.0, after = 0.0;

				if (_needToInit) {
					_x1 = _x2 = _y1 = _y2 = *sample;
					_needToInit = false;
				}

				before = *sample;

				after = _b0 * before + _b1 * _x1 + _b2 * _x2 - _a1 * _y1 - _a2 * _y2;

				*sample = after;

				_y2 = _y1;
				_y1 = after;
				_x2 = _x1;
				_x1 = before;
			}
		}

		void ProcessMonoBlock(T** output, const unsigned long& frameCount)
		{
			if (_active) {
				P before = 0.0, after = 0.0;
				;
				T* mono_out = output[0];
				P x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2;
				P a1 = _a1, a2 = _a2;
				P b0 = _b0, b1 = _b1, b2 = _b2;

				if (_needToInit) {
					x1 = x2 = y1 = y2 = *mono_out;
					_needToInit = false;
				}

				for (unsigned long i = 0; i < frameCount; i++) {
					before = *mono_out;

					after = b0 * before + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;

					*mono_out++ = after;

					y2 = y1;
					y1 = after;
					x2 = x1;
					x1 = before;
				}

				_x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;
			}
		}

		//            void ProcessStereoSample(T* output)
		//            {
		//                if(_active)
		//                {
		//                    P before_left = 0.0, before_right = 0.0;
		//                    P after_left = 0.0, after_right = 0.0;
		//                    P x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2;
		//                    P rx1 = _rx1, rx2 = _rx2, ry1 = _ry1, ry2 = _ry2;
		//                    P a0 = _a0, a1 = _a1, a2 = _a2;
		//                    P b0 = _b0, b1 = _b1, b2 = _b2;
		//
		//                    if(_needToInit)
		//                    {
		//                        x1 = x2 = y1 = y2 = output[0];
		//                        rx1 = rx2 = ry1 = ry2 = output[1];
		//                        _needToInit = false;
		//                    }
		//
		//                    //for(unsigned long i = 0; i < frameCount; i++)
		//                    //{
		//
		//                        before_left = output[0];
		//                        before_right = output[1];
		//
		//                        after_left = (b0 * before_left + b1 * x1 + b2
		//                        * x2 -
		//                                      a1 * y1 - a2 * y2) / a0;
		//
		//                        after_right = (b0 * before_right + b1 * rx1 +
		//                        b2 * rx2 -
		//                                       a1 * ry1 - a2 * ry2) / a0;
		//
		//                        //                        std::cout <<
		//                        after_left << std::endl;
		//                        output[0] = after_left;
		//                        output[1] = after_right;
		//
		//                        y2 = y1;
		//                        y1 = after_left;
		//                        x2 = x1;
		//                        x1 = before_left;
		//
		//                        ry2 = ry1;
		//                        ry1 = after_right;
		//                        rx2 = rx1;
		//                        rx1 = before_right;
		//                    //}
		//
		//                    _x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;
		//                    _rx1 = rx1, _rx2 = rx2, _ry1 = ry1, _ry2 = ry2;
		//                }
		//            }

		void ProcessStereoBlock(T** output, const unsigned long& frameCount)
		{
			if (_active) {
				P before_left = 0.0, before_right = 0.0;
				P after_left = 0.0, after_right = 0.0;
				T *left = output[0], *right = output[1];
				P x1 = _x1, x2 = _x2, y1 = _y1, y2 = _y2;
				P rx1 = _rx1, rx2 = _rx2, ry1 = _ry1, ry2 = _ry2;
				P a0 = _a0, a1 = _a1, a2 = _a2;
				P b0 = _b0, b1 = _b1, b2 = _b2;

				if (_needToInit) {
					x1 = x2 = y1 = y2 = *left;
					rx1 = rx2 = ry1 = ry2 = *right;
					_needToInit = false;
				}

				for (unsigned long i = 0; i < frameCount; i++) {

					before_left = *left;
					before_right = *right;

					after_left = (b0 * before_left + b1 * x1 + b2 * x2 - a1 * y1
									 - a2 * y2) / a0;

					after_right = (b0 * before_right + b1 * rx1 + b2 * rx2
									  - a1 * ry1 - a2 * ry2) / a0;

					//                        std::cout << after_left <<
					//                        std::endl;
					*left++ = after_left;
					*right++ = after_right;

					y2 = y1;
					y1 = after_left;
					x2 = x1;
					x1 = before_left;

					ry2 = ry1;
					ry1 = after_right;
					rx2 = rx1;
					rx1 = before_right;
				}

				_x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;
				_rx1 = rx1, _rx2 = rx2, _ry1 = ry1, _ry2 = ry2;
			}
		}

	private:
		P _a0, _a1, _a2, _b0, _b1, _b2;
		P _x1, _x2, _y1, _y2;
		P _rx1, _rx2, _ry1, _ry2;
		P _freq, _q, _gain;
		Type _type;
		bool _active, _needToInit;
		unsigned long _samplingRate;

		void ComputeCoefficients()
		{
			_freq = ax::Audio::Clamp<P>(_freq, P(1.0), P(_samplingRate * 0.5));

			_q = ax::Audio::Clamp<P>(_q, P(0.1), P(100.0));
			_gain = ax::Audio::Clamp<P>(_gain, P(0.0), P(2.0));

			P w0 = ax::Audio::TwoPi * _freq / double(_samplingRate);
			P c = cos(w0);
			P alpha = sin(w0) / (2.0 * _q);

			switch (_type) {
			case Allpass: // Not supported yet.
			case Lowpass:
				_b0 = _b2 = (1.0 - c) * 0.5;
				_b1 = 1.0 - c;
				_a0 = 1.0 + alpha;
				_a1 = -2.0 * c;
				_a2 = 1.0 - alpha;
				break;

			case Highpass:
				_b0 = (1.0 + c) * 0.5;
				_b1 = -(1.0 + c);
				_b2 = _b0;
				_a0 = 1.0 + alpha;
				_a1 = -2.0 * c;
				_a2 = 1.0 - alpha;
				break;

			case Bandpass:
				_b0 = alpha;
				_b1 = 0.0;
				_b2 = -alpha;
				_a0 = 1.0 + alpha;
				_a1 = -2.0 * c;
				_a2 = 1.0 - alpha;
				break;

			case Notch: {
				P cosW0 = cos(w0);
				_b0 = 1.0;
				_b1 = -2.0 * cosW0;
				_b2 = 1.0;
				_a0 = 1.0 + alpha;
				_a1 = -2.0 * cosW0;
				_a2 = 1.0 - alpha;
			} break;

			case Peak: {
				P cosW0 = cos(w0);
				_b0 = 1.0 + alpha * _gain;
				_b1 = -2.0 * cosW0;
				_b2 = 1.0 - alpha * _gain;
				_a0 = 1.0 + alpha / _gain;
				_a1 = -2.0 * cosW0;
				_a2 = 1.0 - alpha / _gain;
			} break;

			case LowShelf: {
				P cosW0 = cos(w0);
				P sqrtGain = sqrt(_gain);
				P twoGainAlpha = 2.0 * sqrtGain * alpha;
				P gainPlus = _gain + 1.0, gainMinus = _gain - 1.0;

				_b0 = _gain * (gainPlus - gainMinus * cosW0 + twoGainAlpha);
				_b1 = 2.0 * _gain * (gainMinus - gainPlus * cosW0);
				_b2 = _gain * (gainPlus - gainMinus * cosW0 - twoGainAlpha);
				_a0 = gainPlus + gainMinus * cosW0 + twoGainAlpha;
				_a1 = -2.0 * (gainMinus + gainPlus * cos(w0));
				_a2 = gainPlus + gainMinus * cosW0 - twoGainAlpha;
			} break;

			case HighShelf: {
				P cosW0 = cos(w0);
				P sqrtGain = sqrt(_gain);
				P twoGainAlpha = 2.0 * sqrtGain * alpha;
				P gainPlus = _gain + 1.0, gainMinus = _gain - 1.0;

				_b0 = _gain * (gainPlus + gainMinus * cosW0 + twoGainAlpha);
				_b1 = -2.0 * _gain * (gainMinus + gainPlus * cosW0);
				_b2 = _gain * (gainPlus + gainMinus * cosW0 - twoGainAlpha);
				_a0 = gainPlus - gainMinus * cosW0 + twoGainAlpha;
				_a1 = 2.0 * (gainMinus - gainPlus * cosW0);
				_a2 = gainPlus - gainMinus * cosW0 - twoGainAlpha;
			} break;
			
			}

			// Normalize.
			//                _b0 /= _a0;
			//                _b1 /= _a0;
			//                _b2 /= _a0;
			//                _a1 /= _a0;
			//                _a2 /= _a0;
			//                _a0 = 1.0;
		}
	};
}
}

#endif // __AX_AUDIO_BIQUAD_FILTER__