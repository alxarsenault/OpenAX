#ifndef axXml_hpp
#define axXml_hpp

#include "Utils.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

namespace ax {
class Xml {
public:
	struct Exception : public std::exception {
		std::string s;

		Exception(std::string ss)
			: s(ss)
		{
		}

		~Exception() throw()
		{
		} // Updated

		const char* what() const throw()
		{
			return s.c_str();
		}
	};
	
//	class Document {
//	public:
//		Document(rapidxml::xml_document<>* doc)
//			: _xml_doc(doc)
//		{
//			
//		}
//		
//	private:
//		rapidxml::xml_document<>* _xml_doc;
//	};

	class Node {
	public:
		Node(rapidxml::xml_node<>* node);
		
		Node(const Node& node);
		
		Node& operator = (const Node& node);
		
		Node GetNode(const std::string& name);
		
		std::string GetAttribute(const std::string& att_name);
		
		std::string GetValue();
		
		std::string GetChildNodeValue(const std::string& name);
		
		ax::StringPairVector GetAtributes();
		
		bool IsValid() const;
		
		Node GetNextSibling();
		
		Node GetFirstNode();
		
		std::string GetName();

		rapidxml::xml_node<>* GetNodeHandle()
		{
			return _node;
		}
		
		void AddAttribute(const std::string& name, const std::string& value)
		{
			rapidxml::xml_document<>* doc = _node->document();
			char* nn = doc->allocate_string(name.c_str());
			char* vv = doc->allocate_string(value.c_str());
			_node->append_attribute(doc->allocate_attribute(nn, vv));
		}
		
		void AddNode(Node& node)
		{
			_node->append_node(node._node);
		}
		
		void AddNode(const Node& node)
		{
			_node->append_node(node._node);
		}
		
	private:
		rapidxml::xml_node<>* _node;
	};

	Xml(const std::string& path);
	
	Xml()
	{
		rapidxml::xml_node<>* decl
		= _xml_doc.allocate_node(rapidxml::node_declaration);
		decl->append_attribute(_xml_doc.allocate_attribute("version", "1.0"));
		decl->append_attribute(_xml_doc.allocate_attribute("encoding", "utf-8"));
		_xml_doc.append_node(decl);
	}
	
	void Save(const std::string& path)
	{
		std::ofstream file_stored(path);
		
		file_stored << _xml_doc;
		file_stored.close();
		_xml_doc.clear();
	}
	
	std::string GetString()
	{
		std::stringstream str;
		str << _xml_doc;
		return str.str();
	}
	
	Node GetNode(const std::string& name);

	bool Parse();
	
	bool Parse(const std::string&  content);
	
	Node CreateNode(const std::string& name)
	{
		char* nn = _xml_doc.allocate_string(name.c_str());
		return Node(_xml_doc.allocate_node(rapidxml::node_element, nn));
	}
	
//	Node CreateNode()
//	{
//			rapidxml::xml_node<>* decl
//			= _xml_doc.allocate_node(rapidxml::node_declaration);
//			decl->append_attribute(_xml_doc.allocate_attribute("version", "1.0"));
//			decl->append_attribute(_xml_doc.allocate_attribute("encoding", "utf-8"));
//			_xml_doc.append_node(decl);
//		
//		return Node(decl);
//	}

	void AddMainNode(ax::Xml::Node& node)
	{
		_xml_doc.append_node(node.GetNodeHandle());
	}
	
	Node CreateNode(const std::string& name, const std::string& value)
	{
		char* nn = _xml_doc.allocate_string(name.c_str());
		char* vv = _xml_doc.allocate_string(value.c_str());
		return Node(_xml_doc.allocate_node(rapidxml::node_element, nn, vv));
	}
	
	static ax::Size StringToSize(const std::string& size_str);
	static ax::Color StringToColor(const std::string& color_str);

private:
	std::string _file_path;
	rapidxml::xml_document<> _xml_doc;
	std::vector<char> _xml_buffer;
};
}
#endif /* axXml_hpp */
