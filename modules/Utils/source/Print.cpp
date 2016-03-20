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
 
#include "Print.h"

namespace ax {
namespace Console {
	const std::string COLOR_STRING_ARRAY[] = {
		"\033[0m", // Reset.
		"\033[30m", // Black.
		"\033[31m", // Red.
		"\033[32m", // Green.
		"\033[33m", // Yellow.
		"\033[34m", // Blue.
		"\033[35m", // Magenta.
		"\033[36m", // Cyan.
		"\033[37m", // White.
		"\033[1m\033[30m", // Bold Black.
		"\033[1m\033[31m", // Bold Red.
		"\033[1m\033[32m", // Bold Green.
		"\033[1m\033[33m", // Bold Yellow.
		"\033[1m\033[34m", // Bold Blue.
		"\033[1m\033[35m", // Bold Magenta.
		"\033[1m\033[36m", // Bold Cyan.
		"\033[1m\033[37m" // Bold White.
	};

	std::string GetColorStringFromEnum(const Color& color)
	{
		return COLOR_STRING_ARRAY[color];
	}
}

void Print()
{
	std::cout << Console::COLOR_STRING_ARRAY[0] << std::endl;
}

void Error()
{
	std::cout << std::endl;
}
}