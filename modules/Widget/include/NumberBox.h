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

#ifndef __AX_NUMBER_BOX__
#define __AX_NUMBER_BOX__

/*
 * @file    axNumberBox.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axNumberBox.
 * @date    19/07/2013
 */

/// @defgroup Widgets
/// @{

/// @defgroup NumberBox
/// @{

#include "OpenAX.h"

namespace ax {
	/*
	 * ax::NumberBox.
	 */
	class NumberBox: public ax::Window::Backbone
	{
	public:
		
		/// Shared pointer.
		typedef std::shared_ptr<ax::NumberBox> Ptr;
		
		/*
		 * ax::NumberBox::Flags.
		 */
		class Flags
		{
		public:
			static const ax::Flag SINGLE_IMG;
			static const ax::Flag NO_IMG_RESIZE;
			static const ax::Flag LABEL;
			static const ax::Flag SLIDER;
			static const ax::Flag NO_MOUSE;
		};
		
		/*
		 * ax::NumberBox::Msg.
		 */
		class Msg : public ax::Event::Msg
		{
		public:
			Msg(const double& value);
			
			double GetValue() const;
			
			ax::Event::Msg* GetCopy();
			
		private:
			double _value;
		};
		
		/*
		 * ax::NumberBox::Events.
		 */
		class Events
		{
		public:
			enum : ax::Event::Id { VALUE_CHANGE };
			
			Events()
			{}
			
			Events(ax::Event::Function& fct) { value_change = fct; }
			
			ax::Event::Function value_change;
		};
		
		/*
		 * ax::NumberBox::Info.
		 */
		class Info : public ax::widget::Info
		{
		public:
			Info(const std::string& path);
			
			Info(const ax::StringPairVector& attributes);
			
			Info(const ax::Color& normal_color = ax::Color(0.9),
				const ax::Color& hover_color = ax::Color(0.95),
				const ax::Color& clicked_color = ax::Color(0.92),
				const ax::Color& selected_color = ax::Color(0.9),
				const ax::Color& contour_color = ax::Color(0.5),
				const ax::Color& fontColor = ax::Color(0.1),
				const std::string& img = "",
				const bool& singleImg = false);
			
			// Info needed for debug editor. Derived from axInfo.
			virtual ax::StringVector GetParamNameList() const;
			virtual std::string GetAttributeValue(const std::string& name);
			virtual void SetAttribute(const ax::StringPair& attribute);
			
			ax::Color normal;
			ax::Color hover;
			ax::Color clicking;
			ax::Color selected;
			ax::Color contour;
			ax::Color font_color;
			
			std::string img;
			bool single_img;
		};
		
		/*
		 * ax::NumberBox::axNumberBox.
		 */
		NumberBox(const ax::Rect& rect,
				const ax::NumberBox::Events& events,
				const ax::NumberBox::Info& info,
				ax::Flag flags = 0,
				double value = 0.0,
				ax::FloatRange range = ax::FloatRange(0.0, 1.0),
				ax::Utils::Control::Type type = ax::Utils::Control::axCTRL_FLOAT,
				ax::Utils::Control::Unit m_unit = ax::Utils::Control::axCTRL_NO_UNIT,
				ax::Utils::Control::Interpolation interpolation = ax::Utils::Control::axCTRL_LINEAR,
				std::string label = "");
		
		NumberBox(const ax::Point& pos,
				const ax::NumberBox::Events& events = ax::NumberBox::Events(),
				const ax::NumberBox::Info& info = ax::NumberBox::Info(),
				ax::Flag flags = 0,
				double value = 0.0,
				ax::FloatRange range = ax::FloatRange(0.0, 1.0),
				ax::Utils::Control::Type type = ax::Utils::Control::axCTRL_FLOAT,
				ax::Utils::Control::Unit m_unit = ax::Utils::Control::axCTRL_NO_UNIT,
				ax::Utils::Control::Interpolation interpolation = ax::Utils::Control::axCTRL_LINEAR,
				std::string label = "");
		
		inline static std::shared_ptr<ax::Window::Backbone>
		Create(const ax::Point& pos,
			const ax::NumberBox::Events& events = ax::NumberBox::Events(),
			const ax::NumberBox::Info& info = ax::NumberBox::Info(),
			ax::Flag flags = 0,
			double value = 0.0,
			ax::FloatRange range = ax::FloatRange(0.0, 1.0),
			ax::Utils::Control::Type type = ax::Utils::Control::axCTRL_FLOAT,
			ax::Utils::Control::Unit m_unit = ax::Utils::Control::axCTRL_NO_UNIT,
			ax::Utils::Control::Interpolation interpolation = ax::Utils::Control::axCTRL_LINEAR,
			std::string label = "")
		{
			return ax::NumberBox::Ptr(new ax::NumberBox(pos, events, info, flags, value, range,
				type, m_unit, interpolation, label));
		}
		
		double GetValue();
		
		void SetValue(const double& value)
		{
			_value = value;
			win->Update();
		}
		
	private:
		ax::NumberBox::Events _events;
		ax::Flag _flags;
		ax::Image* _bgImg;
		ax::Font* _font;
		
		ax::Utils::Control::Type _type;
		ax::Utils::Control::Unit _unit;
		ax::FloatRange _range;
		ax::Utils::Control::Interpolation _interpolation;
		
		ax::Color _currentColor;
		int _nCurrentImg;
		double _value;
		double _zeroToOneValue;
		std::string _label;
		
		int _clickPosY;
		
		enum NumberBoxState {
			axNUM_BOX_NORMAL,
			axNUM_BOX_HOVER,
			axNUM_BOX_DOWN
		};
		
		// Events.
		virtual void OnPaint(ax::GC gc);
		
		virtual void OnMouseLeftDown(const ax::Point& pos);
		virtual void OnMouseLeftUp(const ax::Point& pos);
		virtual void OnMouseLeftDragging(const ax::Point& pos);
		virtual void OnMouseEnter(const ax::Point& pos);
		virtual void OnMouseLeave(const ax::Point& pos);
	};
}


/// @}
/// @}
#endif // __AX_NUMBER_BOX__