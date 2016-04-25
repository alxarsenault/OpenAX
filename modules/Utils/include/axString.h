/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axFrameworks.
 *
 * axFrameworks is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * axFrameworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axFrameworks, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#ifndef __axUtils__axString__
#define __axUtils__axString__

/// @defgroup Utils
/// @{

#include <string>
#include <vector>
#include <sstream>

namespace ax {
namespace Utils {
	namespace String {

		typedef std::pair<std::string, std::string> Pair;
		typedef std::vector<Pair> PairVector;

		std::string GetExtension(const std::string& path);

		std::vector<std::string> Split(const std::string& str, const std::string& delimiter);

		void ReplaceCharWithString(std::string& input_str, const char& c,
			const std::string& replacement);

		template <typename T> T str_to_type(const std::string& str)
		{
			std::istringstream iss(str);
			T result;

			if (!(iss >> result)) {
				throw "Dude, you need error handling!";
			}

			return result;
		}
	}
}
}

namespace std {
template <typename T> std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}
}

/// @}
#endif /* defined(__axUtils__axString__) */
