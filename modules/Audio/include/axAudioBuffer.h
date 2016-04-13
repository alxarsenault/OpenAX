/*
 * @file	axAudioBuffer.h
 * @author	Alexandre Arsenault <alexandre.arsenault@polymtl.ca>
 * @date	13/08/2013
 */

#ifndef __AX_AUDIO_BUFFER__
#define __AX_AUDIO_BUFFER__

#include "sndfile.h"
#include <iostream>
//#include <thread>
//#include <mutex>

using namespace std;

typedef float axFloat;

enum axSOUND_ERROR { axNO_ERROR = 0, axOPEN_SND_ERROR };

struct axBufferInfo {
	unsigned long frames;
	int sample_rate, channels;
};

// typedef struct
//{
//  sf_count_t frames;
//  int samplerate, channels, format, sections, seekable;
//} SF_INFO ;

namespace ax {
namespace audio {
	class Buffer {
	public:
		Buffer();
		Buffer(const std::string& snd_path);

		Buffer(const std::string& path, const int& test);

		axSOUND_ERROR OpenSoundFile(const string& snd_path);

		axFloat* GetBuffer();

		axBufferInfo GetBufferInfo();

		int GetSampleRate();

		int GetNumberChannels();

		string GetSoundPath();

		void ShowInfo();

	private:
		// Libsndfile.
		SNDFILE* m_sndFile;
		SF_INFO* m_info;
		
		std::string m_path;
//		sf_count_t m_count;

		float *m_buffer, *m_start, *m_end;

		axBufferInfo _info;
	};
}
}

#endif // __AX_AUDIO_BUFFER__.
