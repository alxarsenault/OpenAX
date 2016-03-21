//#ifndef __AX_AUDIO_SIGNAL_BALANCE__
//#define __AX_AUDIO_SIGNAL_BALANCE__
//
//#include "axAudioUtils.h"
//#include "axAudioBiquadFilter.h"
//
// namespace ax
//{
//    namespace Audio
//    {
//        // T Type of input ouput buffers.
//        // P Type of processing variables.
//        template<typename T = double, typename P = double>
//        class SignalBalance
//        {
//        public:
//            SignalBalance(const unsigned long& sampling_rate,
//                          const P& freq = 20000.0):
//            _samplingRate(sampling_rate),
////            _freq(freq),
//            _active(true),
////            _needToInit(true),
//            _sigFilter(sampling_rate, ax::Audio::BiquadFilter<T, P>::Lowpass,
//            50.0),
//            _cmpFilter(sampling_rate, ax::Audio::BiquadFilter<T, P>::Lowpass,
//            50.0)
//            {
//                _cmpBuffer = new P*[2];
//                _cmpBuffer[0] = new P[1024];
//                _cmpBuffer[1] = new P[1024];
//
////                ComputeCoefficients();
//            }
//
//            void SetSamplingRate(const unsigned long& sr)
//            {
//                _samplingRate = sr;
//                _sigFilter.SetSamplingRate(sr);
//                _cmpFilter.SetSamplingRate(sr);
////                ComputeCoefficients();
//            }
//
//            void SetFreq(const P& freq)
//            {
//                _sigFilter.SetFreq(freq);
//                _cmpFilter.SetFreq(freq);
//            }
//
//            void SetActive(const bool& active)
//            {
//                _active = active;
//            }
//
//            void CopyBufferStereo(T** input, const unsigned long& frameCount)
//            {
//                P* left = _cmpBuffer[0];
//                P* right = _cmpBuffer[1];
//                T* left_in = input[0];
//                T* right_in = input[1];
//
//                for(unsigned long i = 0; i < frameCount; i++)
//                {
//                    *left++ = *left_in++;
//                    *right++ = *right_in++;
//                }
//            }
//
//            P** GetCompareBuffer()
//            {
//                return _cmpBuffer;
//            }
//
//            void ProcessStereoBlock(T** output, T** cmp_input,
//                                    const unsigned long& frameCount)
//            {
//                if(_active)
//                {
//                    T *left = output[0], *right = output[1];
//                    T *cmpLeft = cmp_input[0], *cmpRight = cmp_input[1];
//
////                    P past = _past, rpast = _rpast;
////                    P cmpPast = _cmpPast, rcmpPast = _rcmpPast;
////                    P a = _a, b = _b;
//
////                    if(_needToInit)
////                    {
////                        past = *left;
////                        rpast = *right;
////                        cmpPast = *cmpLeft;
////                        rcmpPast = *cmpRight;
////                        _needToInit = false;
////                    }
//
////                    _sigFilter.ProcessStereoBlock(output, frameCount);
////                    _cmpFilter.ProcessStereoBlock(cmp_input, frameCount);
//
//                    P sig[2], cmp[2];
//                    for(unsigned long i = 0; i < frameCount; i++)
//                    {
//                        sig[0] = abs(left[i]);
//                        sig[1] = abs(right[i]);
//                        cmp[0] = abs(cmpLeft[i]);
//                        cmp[1] = abs(cmpRight[i]);
//
//                        _sigFilter.ProcessStereoSample(sig);
//                        _cmpFilter.ProcessStereoSample(cmp);
//
//
//                        left[i] *= (sig[0] != 0.0 ? cmp[0] / sig[0] : cmp[0]);
//                        right[i] *= (sig[1] != 0.0 ? cmp[1] / sig[1] :
//                        cmp[1]);
//
//
////                        past = a * abs(left[i]) - b * past;
////                        cmpPast = a * abs(cmpLeft[i]) - b * cmpPast;
////
////                        rpast = a * abs(right[i]) - b * rpast;
////                        rcmpPast = a * abs(cmpRight[i]) - b * rcmpPast;
//
////                        left[i] *= (past != 0.0 ? cmpPast / past : cmpPast);
////                        right[i] *= (rpast != 0.0 ? rcmpPast / rpast :
///rcmpPast);
//
////                        std::cout << (past != 0.0 ? cmpPast / past :
///cmpPast)<< std::endl;
//                    }
//
////                    _past = past;
////                    _rpast = rpast;
////                    _cmpPast = cmpPast;
////                    _rcmpPast = rcmpPast;
//                }
//            }
//
//        private:
////            P _a, _b;
////            P _past, _rpast;
////            P _cmpPast, _rcmpPast;
////            P _freq;
//            bool _active;//, _needToInit;
//            unsigned long _samplingRate;
//
//            P** _cmpBuffer;
//
//            ax::Audio::BiquadFilter<T, P> _sigFilter, _cmpFilter;
//
////            void ComputeCoefficients()
////            {
////                _freq = ax::Audio::Clamp<P>(_freq, P(1.0),
////                                            P(_samplingRate * 0.5));
////
////                P w0 = ax::Audio::TwoPi * _freq / double(_samplingRate);
////                P cosW0 = cos(w0);
////                _b = sqrt(pow(2.0 - cosW0, 2.0) - 1.0) - 2.0 + cosW0;
////                _a = 1.0 + _b;
////            }
//        };
//    }
//}
//
//#endif // __AX_AUDIO_SIGNAL_BALANCE__