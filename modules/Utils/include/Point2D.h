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

#ifndef __AX_UTILS_POINT_2D_H__
#define __AX_UTILS_POINT_2D_H__

/// @defgroup Utils
/// @{
#include <iostream>

namespace ax {
namespace Utils {
	/*
	 * ax::Utils::Point2D.
	 */
	template <typename T> class Point2D {
	public:
		Point2D(T X = 0, T Y = 0)
		{
			x = X;
			y = Y;
		}

		T x, y;
		
		template <typename P>
		Point2D<P> Cast() const
		{
			return Point2D<P>((P)x, (P) y);
		}

		Point2D operator*(const Point2D& pt) const
		{
			return Point2D(x * pt.x, y * pt.y);
		}

		Point2D operator*(const T& v) const
		{
			return Point2D(x * v, y * v);
		}

		Point2D& operator*=(const Point2D& pt)
		{
			x *= pt.x;
			y *= pt.y;
			return *this;
		}

		Point2D& operator*=(const T& v)
		{
			x *= v;
			y *= v;
			return *this;
		}

		Point2D operator+(const Point2D& pt) const
		{
			return Point2D(x + pt.x, y + pt.y);
		}

		Point2D operator-(const Point2D& pt) const
		{
			return Point2D(x - pt.x, y - pt.y);
		}

		Point2D& operator+=(const Point2D& pt)
		{
			x += pt.x;
			y += pt.y;
			return *this;
		}

		Point2D& operator-=(const Point2D& pt)
		{
			x -= pt.x;
			y -= pt.y;
			return *this;
		}

		Point2D& operator-=(const T& v)
		{
			x -= v;
			y -= v;
			return *this;
		}

		Point2D& operator=(const T& pt)
		{
			x = pt;
			y = pt;
			return *this;
		}

		Point2D& operator=(const Point2D& pt)
		{
			x = pt.x;
			y = pt.y;
			return *this;
		}

		bool operator==(const Point2D& pt)
		{
			return (x == pt.x && y == pt.y);
		}

		bool operator!=(const Point2D& pt)
		{
			return !(x == pt.x && y == pt.y);
		}

		bool operator<(const Point2D& pt)
		{
			return (x < pt.x && y < pt.y);
		}

		bool operator<=(const Point2D& pt)
		{
			return (x <= pt.x && y <= pt.y);
		}

		bool operator>(const Point2D& pt)
		{
			return (x > pt.x && y > pt.y);
		}

		bool operator>=(const Point2D& pt)
		{
			return (x >= pt.x && y >= pt.y);
		}

		Point2D& operator()(const T& X, const T& Y)
		{
			x = X;
			y = Y;
			return *this;
		}
		
		friend std::ostream& operator<< (std::ostream& stream, const Point2D& point)
		{
			stream << point.x << ", " << point.y;
			return stream;
		}
	};
}
}

/// @}
#endif // __AX_UTILS_POINT_2D_H__
