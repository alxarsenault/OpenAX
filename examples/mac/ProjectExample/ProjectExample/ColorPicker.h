//
//  ColorPicker.hpp
//  ProjectExample
//
//  Created by Alexandre Arsenault on 2016-04-06.
//  Copyright © 2016 Alexandre Arsenault. All rights reserved.
//

#ifndef ColorPicker_hpp
#define ColorPicker_hpp

#include <OpenAX/OpenAX.h>

#include <OpenAX/Button.h>
#include <OpenAX/Slider.h>
#include <OpenAX/TextBox.h>

namespace ax {
	class ColorPicker : public ax::Window::Backbone {
	public:
		ColorPicker(const ax::Rect& rect, const ax::Color& color);
		
	private:
		ax::Color _color;
		ax::Font _font;
		ax::Slider* _sliders[4];
		ax::TextBox* _txt_boxes[4];
		
		enum ColorIndex { RED, GREEN, BLUE, ALPHA };
		
		void SetColor(ColorIndex index, double v);
		
		double GetColor(int index);
		
		void TextBoxEvent(ColorIndex index, const std::string& txt);
		
		// Slider events.
		axEVENT_DECLARATION(ax::Slider::Msg, OnRedSlider);
		axEVENT_DECLARATION(ax::Slider::Msg, OnGreenSlider);
		axEVENT_DECLARATION(ax::Slider::Msg, OnBlueSlider);
		axEVENT_DECLARATION(ax::Slider::Msg, OnAlphaSlider);
		
		// Textbox events.
		axEVENT_DECLARATION(ax::TextBox::Msg, OnRedTxt);
		axEVENT_DECLARATION(ax::TextBox::Msg, OnGreenTxt);
		axEVENT_DECLARATION(ax::TextBox::Msg, OnBlueTxt);
		axEVENT_DECLARATION(ax::TextBox::Msg, OnAlphaTxt);

		void OnPaint(ax::GC gc);
	};
}

#endif /* ColorPicker_hpp */
