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

#ifndef __AX_KNOB_H__
#define __AX_KNOB_H__

/*
 * @file    axKnob
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axKnob.
 * @date    12/01/2015
 */

/// @defgroup Widgets
/// @{

/// @defgroup Knob
/// @{

#include "OpenAX.h"
#include "Xml.h"

namespace ax {
/*
 * ax::Knob.
 */
class Knob : public ax::Window::Backbone {
public:
	/*
	 * ax::Knob::Msg.
	 */
	class Msg : public ax::Event::Msg {
	public:
		Msg(const double& value, const std::string& msg);

		double GetValue() const;

		std::string GetMsg() const;

		ax::Event::Msg* GetCopy();

	private:
		double _value;
		std::string _msg;
	};

	/*
	 * ax::Knob::Events.
	 */
	class Events {
	public:
		ax::Event::Function value_change;

		Events()
		{
		}

		Events(const ax::Event::Function& fct)
		{
			value_change = fct;
		}
	};

	/*
	 * ax::Knob::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		virtual ax::StringVector GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const ax::StringPair& attribute);
		
		virtual std::vector<widget::ParamInfo> GetParametersInfo() const
		{
			return {
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorNormal"),
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorHover"),
				widget::ParamInfo(widget::ParamType::COLOR, "bgColorClicked"),
				
				widget::ParamInfo(widget::ParamType::FILEPATH, "img_path"),
				widget::ParamInfo(widget::ParamType::FILEPATH, "selected_img_path"),
				
				widget::ParamInfo(widget::ParamType::SIZE, "knob_size"),
				widget::ParamInfo(widget::ParamType::INTEGER, "n_knob") };
		}

		ax::Color bgColorNormal, bgColorHover, bgColorClicked;
		std::string img_path, selected_img_path;
		ax::Size knob_size;
		unsigned int n_knob;
		
		std::shared_ptr<ax::Image> img;
	};

	/*
	 * ax::Knob::Component.
	 */
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

	/*
	 * axKnob::axKnob.
	 */
	Knob(const ax::Rect& rect, const ax::Knob::Events& events, const ax::Knob::Info& info, ax::Flag flags = 0,
		double value = 0.0, const std::string& msg = "");

	double GetValue()
	{
		return _knobValue;
	}

	void SetValue(const double& value, bool callValueChangeEvent = true);

	void SetBackgroundAlpha(const float& alpha)
	{
		_bgAlpha = alpha;
		win->Update();
	}

	ax::Flag GetFlags() const
	{
		return _flags;
	}

	std::string GetMsg() const
	{
		return _msg;
	}

protected:
	ax::Knob::Events _events;
	std::string _msg;
	ax::Flag _flags;
	ax::FloatRange _range;

	std::shared_ptr<ax::Image> _knobImg;
	ax::Color _currentBgColor;
	unsigned int _nCurrentImg;
	double _knobValue;
	int _clickPosY;
	float _bgAlpha;
	double _zeroToOneValue;

	void OnPaint(ax::GC gc);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
};
}

/// @}
/// @}
#endif // __AX_KNOB_H__.
