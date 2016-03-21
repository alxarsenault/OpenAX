#ifndef __AX_AUDIO_CORE__
#define __AX_AUDIO_CORE__

//------------------------------------------------------------------
// On linux : if you get this error:
// bt_audio_service_open: connect() failed: Connection refused (111)
// Solution : sudo apt-get purge bluez-als
//------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include <cmath>
#include "axAudioFrames.h"

#include "portaudio.h"

//-----------------------------------------------------------------------------
// Audio.
//-----------------------------------------------------------------------------

namespace ax {
namespace audio {
	class Core {
	public:
		Core();

		~Core();

		int InitAudio();
		void StartAudio();
		void StopAudio();

		//            virtual int CallbackAudio(const double** input,
		//                                      double** output,
		//                                      const unsigned long& frameCount)
		//            {
		//                double* left = output[0];
		//                double* right = output[1];
		//
		//                for(unsigned long i = 0; i < frameCount; i++)
		//                {
		//                    *left++ = 0.0;
		//                    *right++ = 0.0;
		//                }
		//
		//                return 0;
		//            }

		virtual int CallbackAudio(ax::Audio::Frames<const float, 1>* inputs,
			ax::Audio::Frames<float, 1>* outputs, unsigned long frameCount)
		{
			return 0;
		}

		virtual int CoreCallbackAudio(const float* input, float* output, unsigned long frameCount)
		{
			//                double* left = _output_buffer[0];
			//                double* right = _output_buffer[1];
			//
			//                for(unsigned long i = 0; i < frameCount; i++)
			//                {
			//                    *left++ = 0.0;
			//                    *right++ = 0.0;
			//                }

			//                ax::Audio::Frames<const float, 1> inArray[] =
			//                {{input}, {input + 1}};
			//                ax::Audio::Frames<float, 1> outArray[] =
			//                {{output}, {output + 1}};
			//
			//                CallbackAudio(inArray, outArray, frameCount);

			//                CallbackAudio((const double**)_input_buffer,
			//                              _output_buffer, frameCount);

			//
			//                left = _output_buffer[0];
			//                right = _output_buffer[0];
			//
			//                for(int i = 0; i < frameCount; i++)
			//                {
			//                    *output++ = float(*left++);
			//                    *output++ = float(*right++);
			//                }

			return 0;
		}

		static int myPaCallback(const void* in, void* out,
			unsigned long frameCount, const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags, void* userData)
		{
			//std::cout << "kk" << std::endl;
			Core* audio = static_cast<Core*>(userData);

			float* output = (float*)out;

			// Init output buffer with zeros.
			for (int i = 0; i < frameCount * 2; i++) {
				output[i] = 0.0f;
			}

			return audio->CoreCallbackAudio((const float*)in, (float*)out, frameCount);
		}

		// private:
		PaStreamParameters outputParameters;
		PaStream* stream;
		PaError err;

		double** _output_buffer;
		double** _input_buffer;
	};
}
}

#endif // __AX_AUDIO_CORE__