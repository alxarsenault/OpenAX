//
//  axBufferPlayer.h
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#ifndef __MidiSequencer__axBufferPlayer__
#define __MidiSequencer__axBufferPlayer__

#include "axAudioUtils.h"

namespace ax {
namespace audio {
	class Buffer;

	class BufferPlayer {
	public:
		BufferPlayer();
		BufferPlayer(ax::audio::Buffer* buffer);

		void SetBuffer(ax::audio::Buffer* buffer);

		void Play();

		enum axAudioBufferPlayingType {
			AUDIO_PLAYING_TYPE_PLAY_ONCE,
			AUDIO_PLAYING_TYPE_REPEAT
		};

		void SetPlaySpeed(const double& speed);

		bool IsPlaying() const;

		void SetPlayingType(const axAudioBufferPlayingType& type);

		void ProcessSample(float* out);
		void ProcessBlock(float* out, unsigned long frameCount);

		void ProcessStereoBlock(double** out, const unsigned long& frameCount);

		double GetCursorPercentPosition() const;

		double GetCurrentVolume() const;

	private:
		unsigned long _bufferCurrentIndex;
		ax::audio::Buffer* _buffer;
		float* _bufferData;
		double _currentVolumeValue;
		double _speedBufferRatio;
		double _rms, _rmsNSamples;
		double _speed;
		bool _playing;
		axAudioBufferPlayingType _playingType;

		void ProcessMonoSample(float* out);
		void ProcessMonoBlock(float* out, unsigned long frameCount);

		void ProcessStereoSample(float* out);
		void ProcessStereoBlock(float* out, unsigned long frameCount);

		void ProcessSpeedChangeStereoBlock(
			float* out, unsigned long frameCount);
	};
}
}
#endif /* defined(__MidiSequencer__axBufferPlayer__) */
