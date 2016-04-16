//
//  axXml.cpp
//  eosMidiController
//
//  Created by Alexandre Arsenault on 2016-02-19.
//  Copyright © 2016 ax. All rights reserved.
//

#include "Xml.h"

namespace ax {

ax::Size Xml::StringToSize(const std::string& size_str)
{
	ax::StringVector size_elem = ax::Utils::String::Split(size_str, ",");
	ax::Size size(-1, -1);

	if (size_elem.size() != 2) {
		throw Xml::Exception("Parsing point (invalid format) -> should be \"x, y\".");
		return size;
	}

	size.x = std::stoi(size_elem[0]);
	size.y = std::stoi(size_elem[1]);

	return size;
}

ax::Color Xml::StringToColor(const std::string& color_str)
{
	ax::StringVector color_elem = ax::Utils::String::Split(color_str, ",");
	ax::Color color(0.0f, 0.0f, 0.0f, 1.0f);

	if (color_elem.size() < 3) {
		throw Xml::Exception(
			"Parsing color (not enough argument) -> should be \"r, g, b\" or \"r, g, b, a\".");
		return color;
	}
	else if (color_elem.size() > 4) {
		throw Xml::Exception("Parsing color (too many argument) -> should be \"r, g, b\" or \"r, g, b, a\".");
		return color;
	}

	color.SetRed(std::stoi(color_elem[0]) / 255.0f);
	color.SetGreen(std::stoi(color_elem[1]) / 255.0f);
	color.SetBlue(std::stoi(color_elem[2]) / 255.0f);

	if (color_elem.size() == 4) {
		color.SetAlpha(std::stoi(color_elem[3]) / 255.0f);
	}

	return color;
}

Xml::Xml(const std::string& path)
	: _file_path(path)
{
}

bool Xml::Parse()
{
	// Read the xml file into a vector.
	std::ifstream menu_file_path(_file_path);

	_xml_buffer = std::vector<char>(
		(std::istreambuf_iterator<char>(menu_file_path)), std::istreambuf_iterator<char>());
	_xml_buffer.push_back('\0');

	try {
		_xml_doc.parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		ax::Error("Xml parsing", e.what());
		return false;
	}

	return true;
}

bool Xml::Parse(const std::string& content)
{
	_xml_buffer = std::vector<char>(content.begin(), content.end());
	_xml_buffer.push_back('\0');

	_xml_doc.clear();

	try {
		_xml_doc.parse<0>(&_xml_buffer[0]);
	}
	catch (rapidxml::parse_error& e) {
		ax::Error("Xml parsing", e.what());
		return false;
	}

	return true;
}

Xml::Node Xml::GetNode(const std::string& name)
{
	return Xml::Node(_xml_doc.first_node(name.c_str()));
}

/*
 * Xml::Node.
 */
Xml::Node::Node(rapidxml::xml_node<>* node)
	: _node(node)
{
}

Xml::Node::Node(const Node& node)
	: _node(node._node)
{
}

Xml::Node& Xml::Node::operator=(const Node& node)
{
	_node = node._node;
	return *this;
}

Xml::Node Xml::Node::GetNode(const std::string& name)
{
	return _node->first_node(name.c_str());
}

std::string Xml::Node::GetAttribute(const std::string& att_name)
{
	rapidxml::xml_attribute<>* att = _node->first_attribute(att_name.c_str());

	if (!att) {
		throw Xml::Exception("Parsing attribute name : " + att_name + ".");
		return "";
	}

	return std::string(att->value(), att->value_size());
}

std::string Xml::Node::GetValue()
{
	return std::string(_node->value(), _node->value_size());
}

std::string Xml::Node::GetChildNodeValue(const std::string& name)
{
	rapidxml::xml_node<>* node = _node->first_node(name.c_str());

	if (!node) {
		throw Xml::Exception("Parsing node name : " + name + ".");
		return "";
	}
	return std::string(node->value(), node->value_size());
}

ax::StringPairVector Xml::Node::GetAtributes()
{
	ax::StringPairVector atts;

	rapidxml::xml_attribute<>* att = _node->first_attribute();

	if (!att) {
		throw Xml::Exception("Reading attributes");
		return atts;
	}

	while (att) {
		atts.push_back(ax::StringPair(
			std::string(att->name(), att->name_size()), std::string(att->value(), att->value_size())));

		att = att->next_attribute();
	}

	return atts;
}

bool Xml::Node::IsValid() const
{
	return _node != nullptr;
}

Xml::Node Xml::Node::GetNextSibling()
{
	return Xml::Node(_node->next_sibling());
}

Xml::Node Xml::Node::GetFirstNode()
{
	return Xml::Node(_node->first_node());
}

std::string Xml::Node::GetName()
{
	return std::string(_node->name(), _node->name_size());
}
}