#ifndef __AX_MIDI__
#define __AX_MIDI__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

#define __MACOSX_CORE__
#include "RtMidi.h"

namespace ax {
namespace midi {
	class Note {
	public:
		Note(const int& note, const int& velocity)
			: _note(note)
			, _velocity(velocity)
		{
		}

		int GetNote() const
		{
			return _note;
		}

		int GetVelocity() const
		{
			return _velocity;
		}

	private:
		int _note, _velocity;
	};

	class Core {
	public:
		Core();
		~Core();
		
		std::vector<std::string> GetMidiInputList();
		
		std::string GetCurrentPortName() const;

		
		void SetInputPort(const std::string& port_name);

	protected:
		virtual void OnMidiNoteOn(const Note& msg);
		virtual void OnMidiNoteOff(const Note& msg);

	private:
		RtMidiIn* _midiInHandle;
		int _input_port;

		static void MidiCallBack(double deltatime,
			std::vector<unsigned char>* message, void* userData);
	};
}
}

#endif // __AX_MIDI__