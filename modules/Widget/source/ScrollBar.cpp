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

#include "ScrollBar.h"

ax::ScrollBar::Info::Info()
{
}

ax::ScrollBar::ScrollBar(const ax::Rect& rect, const ScrollBar::Events& events,
	const ScrollBar::Info& info)
	: _handle(nullptr)
	, _events(events)
	, _info(info)
{
	win = ax::Window::Create(rect);
	win->event.OnPaint = ax::WBind<ax::GC>(this, &ScrollBar::OnPaint);
	
	win->event.OnMouseLeftDown
		= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftDown);
	win->event.OnMouseLeftUp
		= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftUp);
	win->event.OnMouseEnter
		= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseEnter);
	win->event.OnMouseLeave
		= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeave);
	
	win->event.OnMouseLeftDragging
	= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseLeftDragging);
	
	win->event.OnMouseMotion
	= ax::WBind<ax::Point>(this, &ScrollBar::OnMouseMotion);

	_imgHeight = 0;
	_panelSize = rect.size;
	_sliderMaxHeight = rect.size.y - (2.0 * _imgHeight);

	double ratio = double(_panelSize.y - rect.size.y) / double(_panelSize.y);

	_sliderHeight = _sliderMaxHeight * (1.0 - ratio);
	_sliderPos = 0;

	_currentScrollBarColor = _info.normal;

	if (_events.value_change) {
		win->AddConnection(
			ax::ScrollBar::Events::VALUE_CHANGE, _events.value_change);
	}
}

void ax::ScrollBar::SetWindowHandle(ax::Window* win)
{
	_handle = win;
	UpdateWindowSize(win->dimension.GetShownRect().size);
}

//
// ax::ScrollBar::ScrollBar(ax::Window* parent,
//                         ax::Window* handle,
//                         const ax::Rect& rect,
//                         const axScrollBarEvents& events,
//                         const axScrollBarInfo& info,
//                         ax::Flag flags) :
//// Heritage.
// axPanel(parent, rect),
//// Members.
//_events(events),
//_info(info),
//_handle(handle),
//_flags(flags),
//_yClickDelta(0),
//_value(0.0)
//{
//    ax::Button::Info btn_info(ax::Color(0.8, 0.0, 0.0),
//                              ax::Color(0.9, 0.0, 0.0),
//                              ax::Color(0.8, 0.0, 0.0),
//                              ax::Color(0.8, 0.0, 0.0),
//                              ax::Color(0.0, 0.0, 0.0),
//                              ax::Color(0.0, 0.0, 0.0));
//
//	//function<void (axButtonMsg)> btnFct();
//
////	_btn[0] = new axButton(this,
////						   ax::Rect(0, 0, 14, 14),
////						   axButtonEvents(),
////						   btn_info,
////
///"/Users/alexarse/Project/axLib/axProjects/MidiSequencer/scrollBar_up.png");
////
////	_btn[1] = new axButton(this,
////						   ax::Rect(0, rect.size.y - 14, 14, 14),
////						   axButtonEvents(),
////						   btn_info,
////
///"/Users/alexarse/Project/axLib/axProjects/MidiSequencer/scrollBar_down.png");
//
//	_imgHeight = 0;
//    _panelSize = rect.size;
//    _sliderMaxHeight = rect.size.y - (2.0 * _imgHeight);
//
//    double ratio = double(_panelSize.y - rect.size.y) / double(_panelSize.y);
//
//    _sliderHeight = _sliderMaxHeight * (1.0 - ratio);
//    _sliderPos = 0;
//
//    _currentScrollBarColor = &_info.normal;
//
//    if(_events.value_change)
//    {
//        AddConnection(axScrollBarEvents::VALUE_CHANGE, _events.value_change);
//    }
//
//}

void ax::ScrollBar::UpdateWindowSize(const ax::Size& size)
{
	//if(_handle != nullptr) {
		_panelSize = size;
		ax::Size win_size(win->dimension.GetSize());
		_sliderMaxHeight = win_size.y;
		
		double ratio = double(_panelSize.y - win_size.y) / double(_panelSize.y);
		
		_sliderHeight = _sliderMaxHeight * (1.0 - ratio);
		
		if (win_size.y <= win_size.y) {
			_sliderPos = 0;
		}
		
		win->Update();
//	}
}

//void ax::ScrollBar::SetPanelSize(const ax::Size& size)
//{
//	ax::Size framSize(GetRect().size);
//	_panelSize = size;
//	_sliderMaxHeight = framSize.y - (2.0 * _imgHeight);
//
//	double ratio = double(_panelSize.y - framSize.y) / double(_panelSize.y);
//
//	_sliderHeight = _sliderMaxHeight * (1.0 - ratio);
//
//	if (size.y <= framSize.y) {
//		_sliderPos = 0;
//	}
//	Update();
//}

double ax::ScrollBar::GetZeroToOneValue() const
{
	return _sliderPos / double(win->dimension.GetRect().size.y - _sliderHeight - 1);
}

void ax::ScrollBar::SetZeroToOneValue(const double& value)
{
	double v = ax::Utils::Clamp<double>(value, 0.0, 1.0);
	_sliderPos = v * double(win->dimension.GetRect().size.y - _sliderHeight - 1);
	// Slider position ratio.
	_value = (_sliderPos - _imgHeight)
	/ double(_sliderMaxHeight - _sliderHeight - 1);
	_value = ax::Utils::Clamp<double>(_value, 0.0, 1.0);
	
	win->PushEvent(ax::ScrollBar::Events::VALUE_CHANGE,
				   new ax::ScrollBar::Msg(""));
	
	if (_handle != nullptr) {
		const ax::Rect& rect(win->dimension.GetRect());
		_handle->dimension.SetScrollDecay(
										  ax::Point(0, _value * (_panelSize.y - rect.size.y)));
	}
	
	win->Update();
	
}

void ax::ScrollBar::OnMouseMotion(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (ax::Rect(0, _sliderPos, rect.size.x, _sliderHeight)
			.IsPointInside(pos)) {
		_currentScrollBarColor = _info.hover;
		win->Update();
	}
	else if (_currentScrollBarColor != _info.normal) {
		_currentScrollBarColor = _info.normal;
		win->Update();
	}
}

void ax::ScrollBar::OnMouseLeftDown(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (ax::Rect(0, _sliderPos, rect.size.x, _sliderHeight)
			.IsPointInside(pos)) {
		_currentScrollBarColor = _info.hover;
		_yClickDelta = pos.y - _sliderPos;

		win->event.GrabMouse();
		win->Update();
	}
}

void ax::ScrollBar::OnMouseLeftUp(const ax::Point& pos)
{
	if (win->event.IsGrabbed()) {
		win->event.UnGrabMouse();
	}
}

void ax::ScrollBar::OnMouseLeftDragging(const ax::Point& position)
{
	const ax::Rect& rect(win->dimension.GetRect());
	ax::Point pos = position - win->dimension.GetAbsoluteRect().position;

	if (_sliderHeight < _sliderMaxHeight) {
		// m_sliderPosition move with mouse position.
		_sliderPos = pos.y - _yClickDelta;

		// If m_sliderPosition reach bottom, clip m_sliderPosition.
		if (_sliderPos + _sliderHeight > rect.size.y - 1) {
			_sliderPos = rect.size.y - 1 - _sliderHeight;
		}

		// Clip top.
		if (_sliderPos < 0) {
			_sliderPos = 0;
		}

		// Slider position ratio.
		_value = (_sliderPos - _imgHeight)
			/ double(_sliderMaxHeight - _sliderHeight - 1);
		_value = ax::Utils::Clamp<double>(_value, 0.0, 1.0);

		win->PushEvent(ax::ScrollBar::Events::VALUE_CHANGE,
			new ax::ScrollBar::Msg(""));

		if (_handle != nullptr) {
			_handle->dimension.SetScrollDecay(
				ax::Point(0, _value * (_panelSize.y - rect.size.y)));
		}

		win->Update();
	}
}

void ax::ScrollBar::OnMouseEnter(const ax::Point& pos)
{
}

void ax::ScrollBar::OnMouseLeave(const ax::Point& pos)
{
	if (_currentScrollBarColor != _info.normal) {
		_currentScrollBarColor = _info.normal;
		win->Update();
	}
}

void ax::ScrollBar::OnPaint(ax::GC gc)
{
	const ax::Rect& rect(win->dimension.GetDrawingRect());
	
	gc.DrawRectangleColorFade(rect, _info.bg_top, _info.bg_bottom);

	gc.SetColor(_currentScrollBarColor);
	ax::Rect bar_rect(0, _sliderPos, rect.size.x, _sliderHeight);
	gc.DrawRectangle(bar_rect);

	gc.SetColor(_info.slider_contour);
	gc.DrawRectangleContour(bar_rect);

	gc.SetColor(_info.contour);
	gc.DrawRectangleContour(rect);
}
