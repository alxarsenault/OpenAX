//
//  axExecProgram.h
//  ProxyServer
//
//  Created by Alexandre Arsenault on 2015-04-27.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __ProxyServer__axExecProgram__
#define __ProxyServer__axExecProgram__

#include "Utils.h"

namespace ax {
namespace Exec {
	std::string ExecuteProgram(const std::string& folder,
		const std::string& path, const ax::StringVector& args);

	std::vector<const char*> GetCharVectorFromArgs(
		const std::string& prog_name, const ax::StringVector& args);

	std::string GetChildProgramOutput(const int& stdin_fd);
}
}

#endif /* defined(__ProxyServer__axExecProgram__) */
