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

#ifndef __axUtils__axRect2D__
#define __axUtils__axRect2D__

/// @defgroup Utils
/// @{

#include "Point2D.h"

namespace ax {
namespace Utils {
	/*
	 * ax::Utils::RectPoints.
	 */
	template <typename T> struct RectPoints {
		RectPoints()
		{
		}

		RectPoints(const T& bl, const T& tl, const T& tr, const T& br)
			: bottom_left(bl)
			, top_left(tl)
			, top_right(tr)
			, bottom_right(br)
		{
		}

		T bottom_left, top_left, top_right, bottom_right;
	};

	/*
	 * ax::Utils::Rect2D.
	 */
	template <typename CPos, typename CSize, typename T> class Rect2D {
	public:
		Rect2D(CPos pt_ = CPos(0, 0), CSize size_ = CSize(0, 0))
			: position(pt_)
			, size(size_)
		{
		}

		Rect2D(T x, T y, T w, T h)
			: position(x, y)
			, size(w, h)
		{
		}
		
		Rect2D(T x, T y, const CSize& size_)
			: position(x, y)
			, size(size_)
		{
		}

		CPos position;
		CSize size;

		template <typename P> Rect2D<Point2D<P>, Point2D<P>, P> Cast() const
		{
			return Rect2D<Point2D<P>, Point2D<P>, P>(
				position.template Cast<P>(), size.template Cast<P>());
		}

		Rect2D operator+(const Rect2D& rect) const
		{
			return Rect2D(position.x + rect.position.x,
				position.y + rect.position.y, size.x + rect.size.x,
				size.y + rect.size.y);
		}

		Rect2D operator-(const Rect2D& rect) const
		{
			return Rect2D(position.x - rect.position.x,
				position.y - rect.position.y, size.x - rect.size.x,
				size.y - rect.size.y);
		}

		bool operator==(const Rect2D& rect)
		{
			return (rect.position.x == position.x
				&& rect.position.y == position.y && rect.size.x == size.x
				&& rect.size.y == size.y);
		}

		bool operator!=(const Rect2D& rect)
		{
			return (
				(rect.position.x != position.x || rect.position.y != position.y)
				|| (rect.size.x != size.x || rect.size.y != size.y));
		}

		bool operator<(const Rect2D& rect)
		{
			return (size.x < rect.size.x && size.y < rect.size.y);
		}

		bool operator<=(const Rect2D& rect)
		{
			return (size.x <= rect.size.x && size.y <= rect.size.y);
		}

		bool operator>(const Rect2D& rect)
		{
			return (size.x > rect.size.x && size.y > rect.size.y);
		}

		bool operator>=(const Rect2D& rect)
		{
			return (size.x >= rect.size.x && size.y >= rect.size.y);
		}

		bool IsPointInside(const CPos& pos)
		{
			return pos.x >= position.x && pos.x <= position.x + size.x
				&& pos.y >= position.y && pos.y <= position.y + size.y;
		}

		Rect2D GetInteriorRect(const CPos& point) const
		{
			return Rect2D(position.x + point.x, position.y + point.y,
				size.x - (T)(2.0 * point.x), size.y - (T)(2.0 * point.y));
		}

		CPos GetTopLeft() const
		{
			return position;
		}

		CPos GetTopRight() const
		{
			return CPos(position.x + size.x, position.y);
		}

		CPos GetBottomLeft() const
		{
			return CPos(position.x, position.y + size.y);
		}

		CPos GetBottomRight() const
		{
			return CPos(position.x + size.x, position.y + size.y);
		}

		CPos GetMiddle() const
		{
			return CPos(position.x + size.x * 0.5, position.y + size.y * 0.5);
		}

		CPos GetNextPosRight(const T& delta) const
		{
			return CPos(position.x + size.x + delta, position.y);
		}

		CPos GetNextPosDown(const T& delta) const
		{
			return CPos(position.x, position.y + size.y + delta);
		}

		CPos GetNextPosLeft(const T& delta) const
		{
			return CPos(position.x, position.y - delta);
		}

		CPos GetNextPosUp(const T& delta) const
		{
			return CPos(position.x, position.y - delta);
		}

		RectPoints<CPos> GetPoints() const
		{
			return RectPoints<CPos>(CPos(position.x, position.y + size.y),
				CPos(position.x, position.y),
				CPos(position.x + size.x, position.y),
				CPos(position.x + size.x, position.y + size.y));
		}
	};
}
}

/// @}
#endif /* defined(__axUtils__axRect2D__) */
