#include "axAudioEnvelope.h"
#include "AudioUtils.h"
#include "Utils.h"

axAudioEnvelope::axAudioEnvelope()
{
	_sr = 44100;
	_attack = 0.0;
	_sustain = 1.0;
	_decay = 0.0;
	_release = 0.0;

	_nAttackSample = _nDecaySample = _nReleaseSample = 0;

	_buffePos = 0;
	_active = false;
}

void axAudioEnvelope::TriggerNote()
{
	_buffePos = 0;
	_active = true;
}

void axAudioEnvelope::ReleaseNote()
{
}

unsigned int axAudioEnvelope::SecToSample(double seconde)
{
	return seconde * _sr;
}

// double axAudioEnvelope::LineInterpolation(double y1, double y2, double mu)
//{
//	return y1 + mu * (y2 - y1);
//}

void axAudioEnvelope::SetAttack(const float& value)
{
	_attack = value;
	_nAttackSample = ax::audio::SecondeToSample(_attack, _sr); // SecToSample(_attack);
}

void axAudioEnvelope::SetDecay(const float& value)
{
	_decay = value;
	_nDecaySample = ax::audio::SecondeToSample(_decay, _sr); // SecToSample(_decay);
}

void axAudioEnvelope::SetRelease(const float& value)
{
	_release = value;
}

float axAudioEnvelope::Process()
{
	if (_active) {
		// Attack.
		if (_buffePos < _nAttackSample) {
			_buffePos++;
			double mu = _buffePos / double(_nAttackSample);
			return ax::Utils::Interpole::Lineair<float>(0.0, _sustain, mu);
			// return axLineairInterpole<float>(0.0, _sustain, mu);
		}

		// Decay.
		else if (_buffePos < _nDecaySample) {
			_buffePos++;

			double mu = (_buffePos - _nAttackSample) / double(_nDecaySample);
			return ax::Utils::Interpole::Lineair<float>(1.0, 0.0, mu);
		}
	}

	return 0.0;
}