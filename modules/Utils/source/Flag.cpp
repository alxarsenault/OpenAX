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

#include "Flag.h"

namespace ax {
bool IsFlag(const Flag& FLAG, Flag flags)
{
	return ((flags & FLAG) != 0);
}

namespace FlagValue {
	const Flag NO_FLAG = 0;
	const Flag FLAG_1 = 1;
	const Flag FLAG_2 = 2;
	const Flag FLAG_3 = 4;
	const Flag FLAG_4 = 8;
	const Flag FLAG_5 = 16;
	const Flag FLAG_6 = 32;
	const Flag FLAG_7 = 64;
	const Flag FLAG_8 = 128;
	const Flag FLAG_9 = 256;
	const Flag FLAG_10 = 512;
	const Flag FLAG_11 = 1024;
	const Flag FLAG_12 = 2048;
	const Flag FLAG_13 = 4096;
	const Flag FLAG_14 = 8192;
	const Flag FLAG_15 = 16384;
	const Flag FLAG_16 = 32768;
}
}
