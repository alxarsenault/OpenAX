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

private:

	void OnPaint(ax::GC gc);
};
}

#endif // __AX_NUMBER_SCROLL_H__
