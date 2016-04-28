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

#include "Point2D.h"
#include "Rect2D.h"
#include "Range.h"
#include "Interpole.h"
#include "Clamp.h"
#include "axString.h"
#include "Control.h"
#include "Direction.h"
#include "Var.h"
#include "Print.h"
#include "Flag.h"
#include "Color.h"
#include "Property.h"
#include "ResourceStorage.h"
#include "Component.h"
#include "Memory.h"

#include <string>

namespace ax {

// ax::Point
typedef Utils::Point2D<int> Point;

// ax::FloatPoint
typedef Utils::Point2D<float> FloatPoint;

// ax::Size
typedef Utils::Point2D<int> Size;

// ax::FloatSize
typedef Utils::Point2D<float> FloatSize;

// ax::Rect
typedef Utils::Rect2D<Point, Size, int> Rect;

// ax::FloatRect
typedef Utils::Rect2D<FloatPoint, FloatSize, float> FloatRect;

// ax::FloatRange
typedef Utils::Range<float> FloatRange;

// ax::IntRange
typedef Utils::Range<int> IntRange;

// ax::StringPair
typedef Utils::String::Pair StringPair;

// ax::StringPairVector
typedef Utils::String::PairVector StringPairVector;

// ax::Color
/// @brief Template is used to define storage type.
typedef Utils::Color<float> Color;

// ax::Property
typedef Utils::Property<std::string> Property;

// ax::Component
typedef Utils::Component Component;

// ax::ComponentMap
typedef Utils::ComponentMap ComponentMap;
}

/// @}
