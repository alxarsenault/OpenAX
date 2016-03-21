//
//  Terminal.h
//  Minimal
//
//  Created by Alexandre Arsenault on 2015-08-22.
//  Copyright (c) 2015 axLib. All rights reserved.
//

#ifndef __Minimal__Terminal__
#define __Minimal__Terminal__

#include <string>
#include <vector>


namespace ax {
namespace os {
	class File {
	public:
		enum FileType { NONE, FOLDER, UNKNOWN };

		std::string name;
		std::string ext;
		FileType type;
		bool hidden;
	};

	class Directory {
	public:
		Directory();

		void Goto(const std::string& path);

		void GoBack();

		const std::vector<File> GetContent() const;

		std::string GetPath() const;

	private:
		std::string _path;
		std::vector<File> _files;
	};
}
}

#endif /* defined(__Minimal__Terminal__) */
