//
//  axBufferPlayer.h
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#ifndef __AX_AUDIO_WAVE_TABLE__
#define __AX_AUDIO_WAVE_TABLE__

#include "axAudioUtils.h"

#define axBUFFER_SIZE 2048

namespace ax {
namespace audio {
	class Buffer;
	
	class WaveTable {
	public:
		WaveTable();
		WaveTable(ax::audio::Buffer* buffer);

		enum Type {
			axWAVE_TYPE_SINE,
			axWAVE_TYPE_TRIANGLE,
			axWAVE_TYPE_SQUARE,
			axWAVE_TYPE_SAW
		};

		void SetWaveformType(const Type& type);

		void ProcessSample(float* out);
		void ProcessSample(float* out, float* freq);
		void ProcessSample(double* out);
		void ProcessSample(double* out, double* freq);
		void ProcessBlock(float* out, unsigned long frameCount);

		void SetFreq(const double& freq);

		double GetFreq() const;

	private:
		double _freq = { 200.0 };
		float* _data;
		double _cPhase;
		int _bufferSize;

		double WaveInterpole(
			const double& freq, const unsigned int& len, const double& phase);
	};
}
}

#endif // __AX_AUDIO_WAVE_TABLE__
