#ifndef __AX_NUMBER_SCROLL_H__
#define __AX_NUMBER_SCROLL_H__

#include "OpenAX.h"
#include "Button.h"
#include "TextBox.h"

namespace ax {
class NumberScroll : public ax::Window::Backbone {
public:
	enum Events : ax::Event::Id { ASSIGN_VALUE };

	NumberScroll(const ax::Rect& rect, double value);
	
	class Info : public ax::widget::Info {
	public:
		Info();
		
//		/// Info needed for debug editor. Derived from axInfo.
//		virtual ax::StringVector GetParamNameList() const;
//		
//		virtual std::string GetAttributeValue(const std::string& name);
//		
//		virtual void SetAttribute(const ax::StringPair& attribute);
//		
//		virtual std::vector<widget::ParamInfo> GetParametersInfo() const;
		
		std::string up_btn;
		std::string down_btn;
		ax::Button::Info btn_info;
		ax::TextBox::Info txt_info;
	};
	
	void SetValue(double value);

private:
	ax::Button* _btn_up;
	ax::Button* _btn_down;
	ax::TextBox* _txtbox;

	void OnResize(const ax::Size& size);
	void OnPaint(ax::GC gc);
};
}

#endif // __AX_NUMBER_SCROLL_H__
