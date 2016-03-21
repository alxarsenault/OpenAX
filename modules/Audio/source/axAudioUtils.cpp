#include "axAudioUtils.h"

int ax::Audio::SecondeToSample(const double& seconde, const int& samplingRate)
{
	return seconde * samplingRate;
}