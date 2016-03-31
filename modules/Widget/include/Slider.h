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

#ifndef __AX_SLIDER_H__
#define __AX_SLIDER_H__

/// @defgroup Widgets
/// @{

/// @defgroup Slider
/// @{
//
#include "OpenAX.h"

/*
 * axSliderFlags.
*/
//#define axSLIDER_FLAG_VERTICAL ax::FlagValue::FLAG_1
//#define axSLIDER_FLAG_CLICK_ANYWHERE ax::FlagValue::FLAG_2
//#define axSLIDER_FLAG_RELEASE_ON_LEAVE ax::FlagValue::FLAG_3
//#define axSLIDER_FLAG_LEFT_CLICK_ENTER ax::FlagValue::FLAG_4
//#define axSLIDER_FLAG_RIGHT_ALIGN ax::FlagValue::FLAG_5
//#define axSLIDER_FLAG_MIDDLE_ALIGN ax::FlagValue::FLAG_6
//#define axSLIDER_FLAG_BACK_SLIDER ax::FlagValue::FLAG_7
//#define axSLIDER_FLAG_NO_SLIDER_LINE ax::FlagValue::FLAG_8

namespace ax {
/*
 * ax::Slider.
*/
class Slider : public ax::Window::Backbone {
public:
	/*
	 * ax::Slider::Flags.
	 */
	class Flags {
	public:
		static const ax::Flag VERTICAL;
		static const ax::Flag CLICK_ANYWHERE;
		static const ax::Flag RELEASE_ON_LEAVE;
		static const ax::Flag LEFT_CLICK_ENTER;
		static const ax::Flag RIGHT_ALIGN;
		static const ax::Flag MIDDLE_ALIGN;
		static const ax::Flag BACK_SLIDER;
		static const ax::Flag NO_SLIDER_LINE;
	};

	/*
	 * axSliderMsg
	 */
	class Msg : public Event::Msg {
	public:
		Msg(const double& value)
			: _value(value)
		{
		}

		double GetValue() const
		{
			return _value;
		}

		Event::Msg* GetCopy()
		{
			return new ax::Slider::Msg(*this);
		}

	private:
		double _value;
	};

	/*
	 * axSliderEvents.
	 */
	struct Events {
		enum : ax::Event::Id { VALUE_CHANGE };

		Events()
		{
		}

		Events(const ax::Event::Function& fct)
		{
			slider_value_change = fct;
		}

		Event::Function slider_value_change;
	};

	/*
	 * axSliderInfo.
	 */
	class Info : public ax::widget::Info {
	public:
		Info(const std::string& path);
		
		Info(const ax::StringPairVector& attributes);
		
		Info();
		
		/// Info needed for debug editor. Derived from axInfo.
		virtual ax::StringVector GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const ax::StringPair& attribute);
		
		std::string img_path;
		ax::Size btn_size;
		unsigned int slider_width;
		int contour_round_radius = 0;
		
		ax::Color bgColorNormal;
		ax::Color bgColorHover;
		ax::Color bgColorClicked;
		ax::Color sliderColorNormal;
		ax::Color sliderColorHover;
		ax::Color sliderColorClicked;
		ax::Color sliderContourColor;
		ax::Color contourColor;
		ax::Color backSliderColor;
		ax::Color backSliderContourColor;
	};
	
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);
		
		virtual ax::Xml::Node  Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual ax::StringPairVector GetBuilderAttributes();
	};
	
	class Builder : public ax::widget::Builder {
	public:
		Builder();
		
		virtual std::shared_ptr<ax::Window::Backbone> Create(
															 const ax::Point& pos, const std::string& file_path);
		
		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};
//	
//	struct Info {
//		std::string img_path;
//		ax::Size btn_size;
//		unsigned int slider_width;
//		int contour_round_radius = 0;
//
//		ax::Color bgColorNormal, bgColorHover, bgColorClicked,
//			sliderColorNormal, sliderColorHover, sliderColorClicked,
//			sliderContourColor, contourColor, backSliderColor,
//			backSliderContourColor;
//
//		Info()
//		{
//		}
//
//		Info(const std::string& imgPath, const ax::Size& size,
//			const ax::Color& bg_normal, const ax::Color& bg_hover,
//			const ax::Color& bg_clicking, const ax::Color& slider_normal,
//			const ax::Color& slider_hover, const ax::Color& slider_clicking,
//			const ax::Color& slider_contour, const ax::Color& contour,
//			const ax::Color& back_slider, const ax::Color& back_slider_contour,
//			const unsigned int width, const int& contourRadius)
//			: // Members.
//			img_path(imgPath)
//			, btn_size(size)
//			, bgColorNormal(bg_normal)
//			, bgColorHover(bg_hover)
//			, bgColorClicked(bg_clicking)
//			, sliderColorNormal(slider_normal)
//			, sliderColorHover(slider_hover)
//			, sliderColorClicked(slider_clicking)
//			, sliderContourColor(slider_contour)
//			, contourColor(contour)
//			, backSliderColor(back_slider)
//			, backSliderContourColor(back_slider_contour)
//			, slider_width(width)
//			, contour_round_radius(contourRadius)
//		{
//		}
//
//	};

	Slider(const ax::Rect& rect, const Events& events, const Info& info,
		ax::Flag flags = 0);

	void SetBackgroundAlpha(const float& alpha)
	{
		_bg_alpha = alpha;
	}

	void ResizeSlider(const ax::Size& size)
	{
		win->dimension.SetSize(size);
		_sliderYPos = int((size.x - _info.slider_width) * 0.5);
		_btnYPos = int((size.x - _info.btn_size.x) * 0.5);
	}

	double GetValue() const
	{
		return _sliderValue;
	}

	void SetValue(const double& value);
	
	ax::Flag GetFlags() const {
		return _flags;
	}

protected:
	Events _events;
	Info _info;
//	ax::Flag _flag;
	ax::Color _currentBgColor, _currentSliderColor;

	ax::Image _btnImg;
	ax::Flag _flags;

	int _nCurrentImg, _sliderPosition, _btnYPos, _sliderYPos, _delta_click;
	float _bg_alpha;
	double _sliderValue;

	enum axButtonState { axBTN_NORMAL, axBTN_HOVER, axBTN_DOWN };

	void blockSliderPosition(const ax::Point& pos);
	void updateSliderValue();

	void DrawVerticalSlider(ax::GC* gc, const ax::Rect& rect0);
	void DrawLineBehindSlider_Vertical(ax::GC* gc, const ax::Rect& rect0);

	void OnPaint(ax::GC gc);
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseMotion(const ax::Point& pos);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);

	void OnResize(const ax::Size& size);
};
}

/// @}
/// @}
#endif // __AX_SLIDER_H__
