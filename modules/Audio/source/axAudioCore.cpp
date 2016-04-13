#include "axAudio.h"
#include <iostream>

namespace ax {
namespace audio {
	Core::Core()
	{
	}

	Core::~Core()
	{
		StopAudio();
		Pa_Terminate();
		delete[] _output_buffer[0];
		delete[] _output_buffer[1];
		delete[] _output_buffer;
	}

	int Core::InitAudio()
	{
		err = Pa_Initialize();

		if (err != paNoError) {
			std::cerr << "Error." << std::endl;
			exit(1);
		}

		int numDevices;
		numDevices = Pa_GetDeviceCount();
		if (numDevices < 0) {
			std::cerr << "ERROR: Pa_CountDevices returned : " << numDevices
					  << std::endl;
		}

		// If you want to get information about each device,
		// simply loop through as follows.
		const PaDeviceInfo* deviceInfo;
		for (int i = 0; i < numDevices; i++) {
			deviceInfo = Pa_GetDeviceInfo(i);
			 std::cout << "OUTPUT : " << i << " " << deviceInfo->name <<
			 std::endl;
		}

		//----------------------------------------------------------------------
		//----------------------------------------------------------------------
		outputParameters.device = 1; // Pa_GetDefaultOutputDevice();
		//----------------------------------------------------------------------
		//----------------------------------------------------------------------

		if (outputParameters.device == paNoDevice) {
			std::cerr << "Error." << std::endl;
			exit(1);
		}

		// Stereo output.
		outputParameters.channelCount = 2;

		// 32 bit floating point output.
		outputParameters.sampleFormat = paFloat32;

		//	outputParameters.suggestedLatency = Pa_GetDeviceInfo(
		// outputParameters.device )->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;

		err = Pa_OpenStream(&stream,
			NULL, // No input.
			&outputParameters,
			44100, // Sample rate.
			1024, // Buffer size.
			paClipOff, // No cliping.
			myPaCallback, this);

		if (err != paNoError) {
			std::cerr << "Error." << std::endl;
			exit(1);
		}

		_output_buffer = new double*[2];
		_output_buffer[0] = new double[1024];
		_output_buffer[1] = new double[1024];

		return 0;
	}
	
	ax::StringVector Core::GetInputDevices()
	{
		int numDevices = Pa_GetDeviceCount();
		
		if (numDevices < 0) {
			std::cerr << "ERROR: Pa_CountDevices returned : " << numDevices
			<< std::endl;
		}
		
		ax::StringVector devices;
		
		for (int i = 0; i < numDevices; i++) {
			const PaDeviceInfo* device_info = Pa_GetDeviceInfo(i);
			if(device_info->maxInputChannels != 0) {
				devices.push_back(device_info->name);
			}
		}

		return devices;
	}
	
	ax::StringVector Core::GetOutputDevices()
	{
		int numDevices = Pa_GetDeviceCount();
		
		if (numDevices < 0) {
			std::cerr << "ERROR: Pa_CountDevices returned : " << numDevices
			<< std::endl;
		}
		
		ax::StringVector devices;
		
		for (int i = 0; i < numDevices; i++) {
			const PaDeviceInfo* device_info = Pa_GetDeviceInfo(i);
			if(device_info->maxOutputChannels != 0) {
				devices.push_back(device_info->name);
			}
		}
		
		return devices;
	}
	
	std::string Core::GetCurrentInputDevice()
	{
		return std::string("None");
	}
	
	std::string Core::GetCurrentOutputDevice()
	{
		int numDevices = Pa_GetDeviceCount();
		
		if (numDevices < 0) {
			std::cerr << "ERROR: Pa_CountDevices returned : " << numDevices
			<< std::endl;
		}
		
		for (int i = 0; i < numDevices; i++) {
			const PaDeviceInfo* device_info = Pa_GetDeviceInfo(i);
			if(i == outputParameters.device) {
				return std::string(device_info->name);
			}
		}
		
		return std::string("None");
	}

	void Core::StartAudio()
	{
		err = Pa_StartStream(stream);

		if (err != paNoError) {
			std::cerr << "Error openning audio." << std::endl;
			exit(1);
		}
	}

	void Core::StopAudio()
	{
		err = Pa_StopStream(stream);

		if(err == paNoError) {
			return;
		}
		
		if(err == paStreamIsStopped) {
			std::cerr << "Audio is already stoped." << std::endl;
			return;
		}
		
		std::cerr << "Error stoping audio." << std::endl;
	}
}
}