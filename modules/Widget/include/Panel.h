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

#ifndef __AX_PANEL_H__
#define __AX_PANEL_H__

/*
 * @file    axPanel.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axPanel.
 * @date    01/03/2016
 */

/// @defgroup Widgets
/// @{

/// @defgroup Panel
/// @{

#include "OpenAX.h"
#include "Xml.h"

namespace ax {

/*
 * ax::Panel.
 */
class Panel : public ax::Window::Backbone {
public:
	/*
	 * ax::Panel::Flags.
	 */
	class Flags {
	public:
		//		static const ax::Flag SINGLE_IMG;
		//		static const ax::Flag IMG_RESIZE;
		//		static const ax::Flag CAN_SELECTED;
	};

	/*
	 * ax::Panel::Info.
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

		ax::Color background; /// Normal background color.
		ax::Color contour; /// Contour color.
		int round_corner_radius = 0;
	};

	/*
	 * ax::Panel::Component.
	 */
	class Component : public ax::widget::Component {
	public:
		Component(ax::Window* win, Info* info);

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node);

		virtual void SetSaveChildCallback(
			std::function<void(ax::Xml&, ax::Xml::Node&, ax::Window*)> fct)
		{
			_save_child_callback = fct;
		}
		
		ax::StringPairVector GetBuilderAttributes();
		
		virtual void SetBuilderAttributes(const ax::StringPairVector& attributes);

	private:
		std::function<void(ax::Xml&, ax::Xml::Node&, ax::Window*)>
			_save_child_callback;
	};

	/*
	 * ax::Panel::Builder.
	 */
	class Builder : public ax::widget::Builder {
	public:
		Builder();

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path);

		std::shared_ptr<ax::Window::Backbone> Create(ax::Xml::Node& node);

		virtual void SetCreateCallback(
			std::function<void(ax::Window*, ax::Xml::Node&)> fct)
		{
			_create_callback = fct;
		}

	private:
		void CreateChildren(ax::Xml::Node& node, ax::Panel* panel);

		std::function<void(ax::Window*, ax::Xml::Node&)> _create_callback;
	};

	/*
	 * ax::Panel.
	 */
	Panel(const ax::Rect& rect, const Panel::Info& info, const std::string& bg_img,
		const std::string& name = "", ax::Flag flags = 0);

	ax::Flag GetFlags() const
	{
		return _flags;
	}
	
	std::string GetName() const
	{
		return _name;
	}
	
	void SetName(const std::string& name)
	{
		_name = name;
	}
	
	std::string GetBackgroundImagePath() const
	{
		return _bg_img_path;
	}

protected:
	ax::Flag _flags;
	std::string _bg_img_path;
	std::string _name;
	std::shared_ptr<ax::Image> _bg_img;

	void OnPaint(ax::GC gc);
};
}

/// @}
/// @}
#endif //__AX_BUTTON__
