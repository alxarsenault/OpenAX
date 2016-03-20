//
//  Terminal.h
//  Minimal
//
//  Created by Alexandre Arsenault on 2015-08-22.
//  Copyright (c) 2015 axLib. All rights reserved.
//

#ifndef __AX_OS_TERMINAL_H__
#define __AX_OS_TERMINAL_H__

#include "Object.h"
#include "Utils.h"
#include <thread>
#include <string>

namespace ax {
namespace os {
	class Terminal : public ax::Event::Object {
	public:
		enum : ax::Event::Id {
			READ_CHILD_BEGIN,
			READ_CHILD_OUTPUT,
			READ_CHILD_END
		};

		Terminal(std::shared_ptr<ax::Event::Manager> evt_manager);

		bool Execute(const std::string& program_folder_path,
			const std::string& program_name, const ax::StringVector& args);

		bool Write(const std::string& command);

	private:
		std::thread _read_child_thread;
		int _fd_master;

		static void ReadFromChild(Terminal& terminal, const int& stdin_fd);
	};
}
}

#endif // __AX_OS_TERMINAL_H__
