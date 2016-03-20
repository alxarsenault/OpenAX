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

#ifndef __axUtils__axInterpole__
#define __axUtils__axInterpole__

/// @defgroup Utils
/// @{

#include <cmath>

namespace ax {
namespace Utils {
	namespace Interpole {
		template <typename T> T Lineair(const T& y1, const T& y2, const T& mu)
		{
			return y1 + mu * (y2 - y1);
		}

		template <typename T>
		T Logarithmic(const T& y1, const T& y2, const T& mu)
		{
			return pow(y2, mu) * pow(y1, 1.0 - mu);
		}
	}
}
}

/// @}
#endif /* defined(__axUtils__axInterpole__) */
