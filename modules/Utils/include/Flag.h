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
 
#ifndef __axUtils__axFlag__
#define __axUtils__axFlag__

#include <stdint.h>

/// @defgroup Utils
/// @{

namespace ax {
// Flag.
typedef uint16_t Flag;

bool IsFlag(const Flag& FLAG, Flag flags);

namespace FlagValue {
	extern const Flag NO_FLAG;
	extern const Flag FLAG_1;
	extern const Flag FLAG_2;
	extern const Flag FLAG_3;
	extern const Flag FLAG_4;
	extern const Flag FLAG_5;
	extern const Flag FLAG_6;
	extern const Flag FLAG_7;
	extern const Flag FLAG_8;
	extern const Flag FLAG_9;
	extern const Flag FLAG_10;
	extern const Flag FLAG_11;
	extern const Flag FLAG_12;
	extern const Flag FLAG_13;
	extern const Flag FLAG_14;
	extern const Flag FLAG_15;
	extern const Flag FLAG_16;
}
}

/// @}
#endif /* defined(__axUtils__axFlag__) */
