/*
 * Copyright (c) 2013 Alexandre Arsenault.
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
#ifndef __AX_EVENT__
#define __AX_EVENT__

/// @defgroup Event
/// @{

#include "Msg.h"
#include <functional>

namespace ax {
namespace Event {

	typedef unsigned int Id;

	typedef std::function<void(ax::Event::Msg*)> Function;

/// Event declaration.
/// Declare :
/// ax::Event::Function GetFctName();
#define axEVENT_ACCESSOR(TYPE, FUNC)                                           \
	ax::Event::Function Get##FUNC()                                            \
	{                                                                          \
		return [=](                                                            \
			ax::Event::Msg* x) { return this->FUNC(*static_cast<TYPE*>(x)); }; \
	}

/// Event declaration.
/// Declare :
/// ax::Event::Function GetFctName();
/// void FctName(const MsgType& msg);
#define axEVENT_DECLARATION(type, name)                                        \
	void name(const type& msg);                                                \
	axEVENT_ACCESSOR(type, name)

	class axBindedEvent {
	public:
		axBindedEvent(Function& fct, Msg* msg)
			: _fct(fct)
			, _msg(msg)
		{
		}

		void operator()(void)
		{
			_fct(_msg);
			delete _msg;
		}

	private:
		Function _fct;
		Msg* _msg;
	};

	template <typename Class, typename Member, typename Object>
	inline Function Bind(Object&& obj, Member Class::*mem_ptr)
	{
		return Function(std::bind(
			mem_ptr, std::forward<Object>(obj), std::placeholders::_1));
	}
}
}

/// @}
#endif //__AX_EVENT__
