/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axFrameworks License.
 *
 * OpenAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axFrameworks. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#ifndef __AX_UTILS_PROPERTY_H__
#define __AX_UTILS_PROPERTY_H__

/// @defgroup Utils
/// @{

#include <unordered_set>

namespace ax {
namespace Utils {

	template <typename T> class Property : public std::unordered_set<T> {
	public:
		Property()
		{
		}

		virtual ~Property()
		{
		}

		inline void AddProperty(const T& property)
		{
			this->insert(property);
		}

		inline void RemoveProperty(const T& property)
		{
			this->erase(property);
		}

		inline bool HasProperty(const T& property) const
		{
			return this->find(property) == this->end() ? false : true;
		}
	};
}
}

/// @}
#endif // __AX_UTILS_PROPERTY_H__
