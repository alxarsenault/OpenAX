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

#ifndef __AX_WIDGET__
#define __AX_WIDGET__

#include "Utils.h"
#include "Window.h"
#include "Xml.h"

namespace ax {
namespace widget {
	enum class ParamType {
		INTEGER,
		REAL,
		TEXT,
		FILEPATH,
		COLOR,
		ALIGNEMENT,
		RANGE,
		POINT,
		SIZE,
		BOOLEAN,
		CUSTOM,
	};
	
	typedef std::pair<ParamType, std::string> ParamInfo;
	
	/*
	 * ax::Info.
	 */
	class Info {
	public:
		Info();
		
		Info(const std::string& path);

		virtual ~Info();
		
		std::string GetPath() const;

		bool IsEditable() const;

		virtual std::vector<std::string> GetParamNameList() const;
		
		virtual std::vector<ParamInfo> GetParametersInfo() const
		{
			return std::vector<ParamInfo>();
		}

		virtual void SetAttribute(const ax::StringPair& attribute);

		virtual void SetAttributes(const ax::StringPairVector& attributes);

		virtual std::string GetAttributeValue(const std::string& name);

	private:
		std::string _path;
		bool _isEditable;
	};

	/*
	 * ax::WidgetComponent.
	 */
	class Component : public ax::Component {
	public:
		/// Shared pointer.
		typedef std::shared_ptr<Component> Ptr;

		Component(ax::Window* win, Info* info);

		virtual ~Component();

		bool IsEditable() const;

		bool IsInfoEditable() const;

		bool AcceptChild() const;

		virtual void SetInfo(const ax::StringPairVector& attributes);

		ax::widget::Info* GetInfo();
		
		virtual std::string GetBuilderName() const
		{
			return "None";
		}

		virtual void SetBuilderAttributes(const ax::StringPairVector& attributes);

		virtual ax::StringPairVector GetBuilderAttributes();
		
		virtual std::vector<ParamInfo> GetBuilderAttributesInfo() const
		{
			return std::vector<ParamInfo>();
		}
		
		virtual void ReloadInfo()
		{
		}

		ax::Window* GetWindow()
		{
			return _win;
		}

		virtual ax::Xml::Node Save(ax::Xml& xml, ax::Xml::Node& node)
		{
			return node;
		}
		
		virtual void SetSaveChildCallback(std::function<void(ax::Xml&, ax::Xml::Node&, ax::Window*)> fct)
		{
		}

	protected:
		ax::Window* _win;
		Info* _info;

	private:
		bool _isEditable, _isInfoEditable, _acceptChild;
		std::string _name;
		ax::StringPairVector _builderAttributes;
	};

	class Builder {
	public:
		Builder()
		{
		}

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			const ax::Point& pos, const std::string& file_path)
			= 0;

		virtual std::shared_ptr<ax::Window::Backbone> Create(
			ax::Xml::Node& node)
		{
			return nullptr;
		};
		
		virtual void SetCreateCallback(std::function<void(ax::Window*, ax::Xml::Node&)> fct)
		{
			
		}
	};

	//	class Control : public ax::Utils::Component {
	//	public:
	//		typedef std::shared_ptr<Control> Ptr;
	//
	//		Control(ax::Window* win, const std::string& name)
	//		: _win(win), _name(name)
	//		{
	//		}
	//
	//		std::string GetName() const
	//		{
	//			return _name;
	//		}
	//
	//		virtual void Save(rapidxml::xml_node<>* node) = 0;
	//
	//		ax::Window* GetWindow()
	//		{
	//			return _win;
	//		}
	//
	//	private:
	//		ax::Window* _win;
	//		std::string _name;
	//
	//	};
}
}

#endif //__AX_WIDGET__
