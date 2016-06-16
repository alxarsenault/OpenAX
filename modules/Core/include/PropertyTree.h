#ifndef __AX_PROPERTY_TREE_H__
#define __AX_PROPERTY_TREE_H__

#include "Utils.h"
#include "Widget.h"
#include <map>

namespace ax {
	class PropertyTree {
		public:
		PropertyTree()
		{
			
		}
		
		void SetAttribute(const std::pair<std::string, std::string>& attribute)
		{
			
		}
		
//		void SetAttributeExample(const StringPair& attribute)
//		{
//			if (attribute.first == "normal") {
//				normal = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "hover") {
//				hover = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "clicking") {
//				clicking = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "selected") {
//				selected = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "contour") {
//				contour = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "font_color") {
//				font_color = ax::Xml::StringToColor(attribute.second);
//			}
//			else if (attribute.first == "corner_radius") {
//				corner_radius = std::stoi(attribute.second);
//			}
//		}
		
	private:
		std::map<ax::widget::ParamType, std::string> _properties;
		std::map<std::string, void*> _property_handles;
//		std::vector<widget::ParamInfo> _props_info;
//		std::vector<void*> _attributes;
	};
}

#endif // __AX_PROPERTY_TREE_H__
