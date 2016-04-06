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

#ifndef __AX_TOGGLE__
#define __AX_TOGGLE__

/*
 * @file    axToggle
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axToggle.
 * @date    19/07/2013
 */

/// @defgroup Widgets
/// @{

/// @defgroup Toggle
/// @{

#include "OpenAX.h"
#include <fstream>

namespace ax {
/*
 * ax::Toggle.
 */
class Toggle : public ax::Window::Backbone {
public:
	/*
	 * ax::Toggle::Flags.
	 */
	class Flags {
	public:
		static const ax::Flag SINGLE_IMG;
		static const ax::Flag IMG_RESIZE;
		static const ax::Flag CLICK_ON_LEFT_DOWN;
		static const ax::Flag CANT_UNSELECT_WITH_MOUSE;
	};

	/*
	 * ax::Toggle::Msg.
	 */
	class Msg : public ax::Event::Msg {
	public:
		Msg();

		Msg(ax::Toggle* sender, const bool& selected);

		Msg(ax::Toggle* sender, const bool& selected, const std::string& msg);

		ax::Toggle* GetSender() const;

		bool GetSelected() const;

		std::string GetMsg() const;

		ax::Event::Msg* GetCopy();

	private:
		ax::Toggle* _sender;
		bool _selected;
		std::string _msg;
	};

	/*
	 * axToggle::Events.
	 */
	class Events {
	public:
		enum : ax::Event::Id { BUTTON_CLICK };

		ax::Event::Function button_click;

		Events()
		{
		}

		Events(const ax::Event::Function& fct)
		{
			button_click = fct;
		}
	};

	/*
	 * axToggle::Info.
	 */
	class Info : public ax::widget::Info {
	public:
		Info();

		ax::Color normal;
		ax::Color hover;
		ax::Color clicking;

		ax::Color selected;
		ax::Color selected_hover;
		ax::Color selected_clicking;

		/// @todo Add select font color to axToggle.
		ax::Color selected_font_color;

		ax::Color contour;
		ax::Color font_color;
		int font_size = 12;

		std::string img;
		bool single_img;
		
		/// Info needed for debug editor. Derived from axInfo.
		virtual ax::StringVector GetParamNameList() const;
		virtual std::string GetAttributeValue(const std::string& name);
		virtual void SetAttribute(const ax::StringPair& attribute);
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

	/*
	 * ax::Toggle::axToggle.
	 */
	Toggle(const ax::Rect& rect, const Events& events, const Info& info,
		std::string img_path = "", std::string label = "", ax::Flag flags = 0,
		std::string msg = "");

	void SetMsg(const std::string& msg);

	void SetSelected(const bool& selected);
	
	bool IsSelected() const
	{
		return _selected;
	}
	
	std::string GetLabel() const
	{
		return _label;
	}
	
	std::string GetMsg() const
	{
		return _msg;
	}
	
	ax::Flag GetFlags() const
	{
		return _flags;
	}
	
	std::string GetImagePath() const
	{
		return _bgImg->GetImagePath();
	}
	
	

protected:
	enum ToggleState {
		axTOG_NORMAL,
		axTOG_HOVER,
		axTOG_CLICK,
		axTOG_SEL_NORMAL,
		axTOG_SEL_HOVER,
		axTOG_SEL_CLICK
	};

	int _nCurrentImg;

	ax::Toggle::Events _events;

	ax::Color _currentColor;
	std::shared_ptr<ax::Image> _bgImg;
	std::string _label;
	std::string _msg;
	std::unique_ptr<ax::Font> _font;
	ax::Toggle::Info* _info;

	bool _selected;
	ax::Flag _flags;
	ax::Color test;
	double _bgAlpha;

	// Events.
	virtual void OnPaint(ax::GC gc);
	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	virtual void OnMouseEnter(const ax::Point& pos);
	virtual void OnMouseLeave(const ax::Point& pos);
};
}
/// @}
/// @}
#endif //__AX_TOGGLE__