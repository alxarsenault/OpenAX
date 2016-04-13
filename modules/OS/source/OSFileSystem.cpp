

#include "OSFileSystem.h"
#include <dirent.h>

#include "Utils.h"

namespace ax {
namespace os {
	Directory::Directory()
	{
	}

	void Directory::GoBack()
	{
		if (_path != "/") {
			std::string new_path = _path.substr(0, _path.size() - 2);

			std::size_t pos = new_path.find_last_of("/");

			if (pos == std::string::npos) {
				ax::Error("Can't find last path.");
				return;
			}

			new_path = new_path.substr(0, pos + 1);

//			ax::Print(new_path);

			Goto(new_path);
		}
	}

	void Directory::Goto(const std::string& path)
	{
		_path = path;
		DIR* dirp;
		struct dirent* dp;

		if ((dirp = opendir(path.c_str())) == nullptr) {
			ax::Error("Can't open directory.");
			return;
		}

		_files.clear();

		do {
			if ((dp = readdir(dirp)) != nullptr) {
				std::string d_name(dp->d_name);

				if (d_name == "." || d_name == "..") {
					continue;
				}

				ax::os::File file;
				file.name = dp->d_name;

				// File.
				if (dp->d_type == DT_REG) {
					file.ext = ax::Utils::String::GetExtension(file.name);
					file.type = ax::os::File::FileType::UNKNOWN;
				}
				else {
					file.ext = ax::Utils::String::GetExtension(file.name);
					file.type = ax::os::File::FileType::FOLDER;
				}

				_files.push_back(file);
			}

		} while (dp != nullptr);

		closedir(dirp);
	}

	std::string Directory::GetPath() const
	{
		return _path;
	}

	const std::vector<File> Directory::GetContent() const
	{
		return _files;
	}
}
}