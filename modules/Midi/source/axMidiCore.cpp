#include "axMidiCore.h"

namespace ax {
namespace midi {
	Core::Core()
	{
		_midiInHandle = new RtMidiIn();

		// Check available ports.
		unsigned int nPorts = _midiInHandle->getPortCount();

		if (nPorts == 0) {
			std::cout << "No ports available!\n";

			/// @todo Trhow exception.
		}
		for (int i = 0; i < nPorts; i++) {
			//                std::cout << _midiInHandle->RtMidi::getPortName()
			//                << std::endl;
			std::cout << _midiInHandle->getPortName() << std::endl;
		}

		// for(int i = 0; i < nPorts; i++)
		// {
		//     _midiInHandle->openPort(i);
		// }
		_midiInHandle->openPort(0);
		//            _midiInHandle->openPort( 0 );

		// Set our callback function.  This should be done immediately after
		// opening the port to avoid having incoming messages written to the
		// queue.
		_midiInHandle->setCallback(&MidiCallBack, (void*)this);

		// Don't ignore sysex, timing, or active sensing messages.
		_midiInHandle->ignoreTypes(false, false, false);

		// cleanup:
		//    delete midiin;
	}

	Core::~Core()
	{
	}

	void Core::OnMidiNoteOn(const Note& msg)
	{
	}

	void Core::OnMidiNoteOff(const Note& msg)
	{
	}

	void Core::MidiCallBack(
		double deltatime, std::vector<unsigned char>* message, void* userData)
	{
		unsigned int nBytes = (unsigned int)message->size();

		if (nBytes >= 3) {
			Note midiMsg(message->at(1), message->at(2));
			Core* midi = static_cast<Core*>(userData);

			if (message->at(0) == 144) {
				midi->OnMidiNoteOn(midiMsg);
				//            std::cout << "Note on : " << (int)message->at(1)
				//            << " velocity : " << (int)message->at(2) <<
				//            std::endl;
			}
			else if (message->at(0)) {
				midi->OnMidiNoteOff(midiMsg);
				//            std::cout << "Note off : " << (int)message->at(1)
				//            << " velocity : " << (int)message->at(2) <<
				//            std::endl;
			}
		}
	}
}
}
