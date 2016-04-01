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

/// @defgroup Utils
/// @{

#ifndef __axUtils__axRange__
#define __axUtils__axRange__

namespace ax {
namespace Utils {
	/*
	 * ax::Utils::Range.
	 */
	template <typename T> class Range {
	public:
		Range()
		{
		}

		Range(const T& minimum, const T& maximum)
			: left(minimum)
			, right(maximum)
		{
		}

		double GetZeroToOneValue(const double& value) const
		{
			double v = double(value - left) / double(right - left);
			if (v > 1.0)
				v = 1.0;
			if (v < 0.0)
				v = 0.0;

			return v;
		}

		double GetValueFromZeroToOne(const double& value)
		{
			double v = double(left) + value * double(right - left);
			if (v > right)
				v = right;
			if (v < left)
				v = left;
			return v;
		}

		T left, right;
	};
}
}

/// @}
#endif /* defined(__axUtils__axRange__) */
