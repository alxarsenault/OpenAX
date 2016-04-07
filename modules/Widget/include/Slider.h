/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of OpenAX.
 *
 * OpenAX is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * license or use a commercial OpenAX License.
 *
 * OpenAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenAX. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses OpenAX, commercial
 * licenses are available, email ax.frameworks@gmail.com for more information.
 */

#ifndef __AX_SLIDER_H__
#define __AX_SLIDER_H__

/// @defgroup Widgets
/// @{

/// @defgroup Slider
/// @{
//
#include "OpenAX.h"

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
		Msg(Slider* slider, const double& value)
			: _slider(slider)
			, _value(value)
		{
		}

		double GetValue() const
		{
			return _value;
		}

		Slider* GetSender() const
		{
			return _slider;
		}

		Event::Msg* GetCopy()
		{
			return new ax::Slider::Msg(*this);
		}

	private:
		double _value;
		ax::Slider* _slider;
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
		
		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return {
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorNormal"),
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorHover"),
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorClicked"),
				
				widget::ParamInfo(widget::ParamType::COLOR, "sliderColorNormal"),
				widget::ParamInfo(widget::ParamType::COLOR, "sliderColorHover"),
				widget::ParamInfo(widget::ParamType::COLOR, "sliderColorClicked"),
				widget::ParamInfo(widget::ParamType::COLOR, "sliderContourColor"),
				
				widget::ParamInfo(widget::ParamType::COLOR, "contourColor"),
				widget::ParamInfo(widget::ParamType::COLOR, "backSliderColor"),
				widget::ParamInfo(widget::ParamType::COLOR, "backSliderContourColor"),
				
				widget::ParamInfo(widget::ParamType::FILEPATH, "img_path"),
				widget::ParamInfo(widget::ParamType::SIZE, "btn_size"),
				widget::ParamInfo(widget::ParamType::INTEGER, "slider_width"),
				widget::ParamInfo(widget::ParamType::INTEGER, "contour_round_radius")  };
		}

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
		
		std::string img_path;
		ax::Size btn_size;
		unsigned int slider_width;
		int contour_round_radius = 0;
	};

	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);
		virtual ax::StringPairVector GetBuilderAttributes();
	};

	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);
	};

	Slider(const ax::Rect& rect, const Events& events, const Info& info, ax::Flag flags = 0);

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

	ax::Flag GetFlags() const
	{
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
