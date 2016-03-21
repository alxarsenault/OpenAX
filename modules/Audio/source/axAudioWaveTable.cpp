//
//  axBufferPlayer.cpp
//  MidiSequencer
//
//  Created by Alexandre Arsenault on 2014-11-14.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "axAudioWaveTable.h"
#include "axAudioBuffer.h"
#include "axAudioUtils.h"
#include <cmath>

namespace ax {
	namespace audio {
WaveTable::WaveTable()
	: _cPhase(0.0)
	, _bufferSize(axBUFFER_SIZE)
{
	_data = new float[_bufferSize + 1];
	SetWaveformType(axWAVE_TYPE_SINE);
}

WaveTable::WaveTable(ax::audio::Buffer* buffer)
{
	_bufferSize = (int)buffer->GetBufferInfo().frames;
	_data = new float[_bufferSize + 1];

	axFloat* bufferData = buffer->GetBuffer();

	for (int i = 0; i < _bufferSize; i++) {
		_data[i] = bufferData[i];
	}

	_data[_bufferSize] = bufferData[0];
}

void WaveTable::SetWaveformType(const WaveTable::Type& type)
{
	/// @todo Check for buffer size first.
	_bufferSize = axBUFFER_SIZE;
	double one_over_buffer_size = 1.0 / _bufferSize;

	switch (type) {
	case axWAVE_TYPE_SINE: {
		for (int i = 0; i < _bufferSize + 1; i++) {
			_data[i] = sin(i * 2.0 * M_PI * one_over_buffer_size);
		}
	} break;

	case axWAVE_TYPE_TRIANGLE: {
		for (int i = 0; i < _bufferSize; i++) {
			if (2 * i >= _bufferSize) {
				_data[i] = 1 - 2.0 * i * one_over_buffer_size;
			}

			else {
				_data[i] = 2.0 * i * one_over_buffer_size;
			}
		}
		_data[_bufferSize] = _data[0];

	} break;

	case axWAVE_TYPE_SQUARE: {
		for (int i = 0; i < _bufferSize + 1; i++) {
			_data[i] = sin(i * 2.0 * M_PI * one_over_buffer_size);

			if (_data[i] > 0) {
				_data[i] = 1;
			}

			if (_data[i] < 0) {
				_data[i] = -1;
			}
		}
	} break;

	case axWAVE_TYPE_SAW: {
		for (int i = 0; i < _bufferSize; i++) {
			_data[i] = 1.0 - (i * one_over_buffer_size);
		}

		_data[_bufferSize] = _data[0];

	} break;
	}
}

void WaveTable::SetFreq(const double& freq)
{
	_freq = freq;
}

double WaveTable::WaveInterpole(
	const double& freq, const unsigned int& len, const double& phase)
{
	double two_pi = 2.0 * M_PI;

	// PHASOR --> A CHANGER ( ENLEVER FMOD )
	double v = 1.0 - _cPhase * ax::Audio::InvTwoPi;
	_cPhase += ((two_pi / 44100.0) * (freq + phase));

	if (_cPhase > two_pi) {
		_cPhase = fmod(_cPhase, two_pi);
	}
	if (_cPhase < 0.0) {
		_cPhase = fmod(_cPhase, two_pi) * (-1.0);
	}

	// WAVETABLE
	long pos = v * ((double)len - 1.0);
	double frac = v * (double)len - pos;

	return ax::Audio::LineairInterpole<double>(_data[pos], _data[pos + 1], frac);
}

void WaveTable::ProcessSample(float* out)
{
	*out = WaveInterpole(_freq, _bufferSize, 0);
}

void WaveTable::ProcessSample(float* out, float* freq)
{
	*out = WaveInterpole(*freq, _bufferSize, 0);
}

void WaveTable::ProcessSample(double* out)
{
	*out = WaveInterpole(_freq, _bufferSize, 0);
}

void WaveTable::ProcessSample(double* out, double* freq)
{
	*out = WaveInterpole(*freq, _bufferSize, 0);
}

double WaveTable::GetFreq() const
{
	return _freq;
}

void WaveTable::ProcessBlock(float* out, unsigned long frameCount)
{
	for (int i = 0; i < frameCount; i++) {
		double v = WaveInterpole(_freq, _bufferSize, 0);

		*out++ = v;
		*out++ = v;
	}
}
}
}