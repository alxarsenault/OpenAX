/*
 * Copyright (c) 2013 Alexandre Arsenault.
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

#ifndef __AX_SCROLL_BAR__
#define __AX_SCROLL_BAR__

/// @defgroup Widgets
/// @{

/// @defgroup ScrollBar
/// @{

#include "OpenAX.h"

namespace ax {
class ScrollBar : public ax::Window::Backbone {
public:
	typedef std::shared_ptr<ScrollBar> Ptr;

	typedef ax::Event::StringMsg Msg;

	class Events {
	public:
		enum : ax::Event::Id { VALUE_CHANGE };

		Events()
		{
		}

		Events(const ax::Event::Function& fct)
		{
			value_change = fct;
		}

		ax::Event::Function value_change;
	};

	class Info : public ax::widget::Info {
	public:
		Info();

		ax::Color normal;
		ax::Color hover;
		ax::Color clicking;
		ax::Color slider_contour;
		ax::Color contour;
		ax::Color bg_top;
		ax::Color bg_bottom;
	};

	ScrollBar(const ax::Rect& rect, const ScrollBar::Events& events,
		const ScrollBar::Info& info);

	void SetWindowHandle(ax::Window* win);

	void UpdateWindowSize(const ax::Size& size);

	double GetZeroToOneValue() const;
	void SetZeroToOneValue(const double& value);

private:
	ax::ScrollBar::Events _events;
	ax::ScrollBar::Info _info;
	ax::Window* _handle;

	int _imgHeight, _sliderHeight, _sliderMaxHeight, _sliderPos, _yClickDelta;
	ax::Size _panelSize;

	ax::Color _currentScrollBarColor;

	double _value;

	void OnPaint(ax::GC gc);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseMotion(const ax::Point& pos);
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);
};
}

/*
 * axButtonFlags.
*/
// #define axBUTTON_SINGLE_IMG	ax::Flag_1
// #define axBUTTON_IMG_RESIZE	ax::Flag_2

// class axScrollBar;
//
// class axScrollBarMsg : public ax::Event::Msg
//{
// public:
//	axScrollBarMsg()
//	{
//		_sender = nullptr;
//	}
//
//	axScrollBarMsg(axScrollBar* sender, const std::string& msg)
//	{
//		_sender = sender;
//		_msg = msg;
//	}
//
//	axScrollBar* GetSender() const
//	{
//		return _sender;
//	}
//
//    std::string GetMsg() const
//	{
//		return _msg;
//	}
//
//    ax::Event::Msg* GetCopy()
//    {
//        return new axScrollBarMsg(*this);
//    }
//
// private:
//	axScrollBar* _sender;
//	std::string _msg;
//};
//
// struct axScrollBarEvents
//{
//    enum : ax::Event::Id { VALUE_CHANGE };
//
//	axScrollBarEvents(){}
//    axScrollBarEvents(ax::Event::Function& fct){ value_change = fct; }
//
//    ax::Event::Function value_change;
//};
//
// struct axScrollBarInfo
//{
//	ax::Color normal;
//	ax::Color hover;
//	ax::Color clicking;
//	ax::Color slider_contour;
//	ax::Color contour;
//	ax::Color bg_top;
//    ax::Color bg_bottom;
//
//	axScrollBarInfo(){}
//    axScrollBarInfo(const ax::Color& normal_color,
//                    const ax::Color& hover_color,
//                    const ax::Color& clicked_color,
//                    const ax::Color& sliderContour,
//                    const ax::Color& contour_color,
//                    const ax::Color& bgTop,
//                    const ax::Color& bgBottom) :
//    normal(normal_color),
//    hover(hover_color),
//    clicking(clicked_color),
//    slider_contour(sliderContour),
//    contour(contour_color),
//    bg_top(bgTop),
//    bg_bottom(bgBottom)
//    {
//
//    }
//};

//
// class axScrollBar : public axPanel
//{
// public:
//	axScrollBar(ax::Window* parent,
//                ax::Window* handle,
//                const ax::Rect& rect,
//                const axScrollBarEvents& events,
//                const axScrollBarInfo& info,
//                ax::Flag flags = 0);
//
//	double GetZeroToOneValue() const;
//	void SetZeroToOneValue(const double& value);
////	// void setBackgroundImage(wxBitmap& bmp);
////	void setSliderPositionZeroToOne(const double& value);
////	void setInputTopDelta(int y);
////	void setInputFrameHeight(int y);
////	void setInputPanelHeight(int y);
////	void setInputInfo(int frameSize, int panelSize, int topDelta);
////	double getSliderValue() const;
////	inline void recalculateInputValue();
//
//    void SetPanelSize(const ax::Size& size);
//
// private:
//	axScrollBarEvents _events;
//	axScrollBarInfo _info;
//	ax::Flag _flags;
//    ax::Window* _handle;
//
//    ax::Button* _btn[2];
//
//	int _imgHeight, _sliderHeight, _sliderMaxHeight, _sliderPos, _yClickDelta;
//    ax::Size _panelSize;
//
//    ax::Color* _currentScrollBarColor;
//	double _value;
//
//	virtual void OnPaint();
//	virtual void OnMouseLeftDragging(const ax::Point& pos);
//	virtual void OnMouseLeftDown(const ax::Point& pos);
//	virtual void OnMouseLeftUp(const ax::Point& pos);
//    virtual void OnMouseMotion(const ax::Point& pos);
//	virtual void OnMouseEnter();
//	virtual void OnMouseLeave();
//};

/// @}
/// @}
#endif //__AX_SCROLL_BAR__
