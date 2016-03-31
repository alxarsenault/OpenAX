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
 
#ifndef __AX_PRINT_H__
#define __AX_PRINT_H__

/// @defgroup Utils
/// @{

#include <iostream>
#include <string>

namespace ax {
namespace Console {

	enum Color {
		Reset,

		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,

		BoldBlack,
		BoldRed,
		BoldGreen,
		BoldYellow,
		BoldBlue,
		BoldMangenta,
		BoldCyan,
		BoldWhite
	};

	std::string GetColorStringFromEnum(const Color& color);
}

// Since variadic templates are recursive, must have a base case.
void Print();

template <typename T, typename... P> void Print(T t, P... p)
{
	std::cout << t << ' ';
	{
		Print(p...);
	}
}

template <typename T, typename... P>
void Print(const Console::Color& color, T t, P... p)
{
	std::cout << Console::GetColorStringFromEnum(color) << t << ' ';
	{
		Print(p...);
	}
}

// Since variadic templates are recursive, must have a base case.
void Error();

template <typename T, typename... P> void Error(T t, P... p)
{
	std::cerr << "Error : " << t << ' ';
	{
		Print(p...);
	}
}
}

/// @}
#endif // __AX_PRINT_H__
