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

#ifndef __axUtils__axControl__
#define __axUtils__axControl__

/// @defgroup Utils
/// @{

namespace ax {
namespace Utils {
	namespace Control {
		/*
		 * ax::Utils::Control::Type.
		 */
		enum Type { axCTRL_NO_TYPE, axCTRL_FLOAT, axCTRL_INT, axCTRL_PAN };

		/*
		 * ax::Utils::Control::Unit.
		 */
		enum Unit {
			axCTRL_NO_UNIT,
			axCTRL_HERTZ,
			axCTRL_DECIBEL,
			axCTRL_TIME_MS,
			axCTRL_TIME_SEC
		};

		/*
		 * ax::Utils::Control::Interpolation.
		 */
		enum Interpolation {
			axCTRL_LINEAR,
			axCTRL_EXPONENTIAL,
			axCTRL_LOGARITHME
		};
	}
}
}

/// @}
#endif /* defined(__axUtils__axControl__) */
