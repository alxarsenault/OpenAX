//
//  axExecProgram.cpp
//  ProxyServer
//
//  Created by Alexandre Arsenault on 2015-04-27.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "OSExec.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace ax {
namespace Exec {
	std::string ExecuteProgram(const std::string& folder,
		const std::string& name, const std::vector<std::string>& args)
	{
		int filedes[2]; // [0] Read, [1] Write.

		if (pipe(filedes) == -1) {
			perror("pipe");
			std::cerr << "Can't create pipe." << std::endl;
			return "";
		}

		pid_t pid = fork();

		// Fork error.
		if (pid == -1) {
			std::cerr << "Can't create fork process." << std::endl;
			return "";
		}
		// Child process.
		else if (pid == 0) {
			while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {
			}

			// Close stdin and stdout file descriptor.
			close(filedes[1]);
			close(filedes[0]);

			// Get formatted arguments vector.
			std::vector<const char*> char_ptr_args = GetCharVectorFromArgs(name, args);

			std::string program_path = folder + name;

			// Call program.
			execv(program_path.c_str(), (char* const*)char_ptr_args.data());

			std::cerr << "Error : Can't exec." << std::endl;
			return "";
		}

		// Parent process.

		// Close stdout file descriptor.
		close(filedes[1]);

		// Get output from child program stdout.
		std::string program_ouput = GetChildProgramOutput(filedes[0]);

		// Close read file descriptor.
		close(filedes[0]);
		wait(0);

		return program_ouput;
	}

	std::vector<const char*> GetCharVectorFromArgs(
		const std::string& prog_name, const std::vector<std::string>& args)
	{
		std::vector<const char*> char_ptr_args;
		char_ptr_args.reserve(args.size() + 2);

		// Add program name to arguments.
		char_ptr_args.push_back(prog_name.data());

		// Copie all arguments from StringVector.
		for (auto& n : args) {
			char_ptr_args.push_back(n.data());
		}

		// Add end of arguments.
		char_ptr_args.push_back((char*)0);

		return char_ptr_args;
	}

	std::string GetChildProgramOutput(const int& stdin_fd)
	{

		std::string program_ouput = "";
		char buffer[4096];

		// Read output from child program.
		while (1) {
			ssize_t count = read(stdin_fd, buffer, sizeof(buffer));

			if (count == -1) {
				if (errno == EINTR) {
					continue;
				}
				else {
					std::cerr << "Error : parent can't read." << std::endl;
					return "";
				}
			}
			else if (count == 0) {
				break;
			}
			else {

				std::string prog_answer(buffer, count);
				program_ouput += prog_answer;
			}
		}

		return program_ouput;
	}
}
}
