#ifndef __AX_AUDIO_FRAMES__
#define __AX_AUDIO_FRAMES__

#include "axAudioUtils.h"

// std::vector<double>

namespace ax {
namespace Audio {
	template <typename T, size_t _powerOf2> class Frames {
	public:
		Frames(T* data)
			: _data(data) //,
		//            _nFrames(nFrames)
		{
		}

		T& operator[](size_t i)
		{
			return _data[i << _powerOf2];
		}

	private:
		T* _data;
		// unsigned long _nFrames;
	};

	//        template<typename T = double>
	//        class Frames
	//        {
	//        public:
	//            Frames(const unsigned int nInput,
	//                   const bool& inputInterlace,
	//                   T** input,
	//                   const unsigned int nOutput,
	//                   const bool& outputInterlace
	//                   T** ouput,
	//                   const unsigned long& nFrames):
	//            _nInput(nInput),
	//            _inputInterlace(inputInterlace),
	//            _input(input),
	//            _nOutput(nOutput),
	//            _outputInterlace(outputInterlace),
	//            _output(ouput),
	//            _nFrames(nFrames)
	//            {
	//
	//            }
	//
	//            T begin()
	//            {
	//
	//            }
	//
	//            T end()
	//            {
	//
	//            }
	//
	//
	//        private:
	//            unsigned int _nInput, _nOutput;
	//            bool _inputInterlace, _outputInterlace;
	//            unsigned long _nFrames;
	//            T** _output;
	//            T** _input;
	//        };
}
}

#endif // __AX_AUDIO_FRAMES__