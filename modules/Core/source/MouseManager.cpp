/*
 * Copyright (c) 2016 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 */

#include "MouseManager.h"
#include "Window.h"
#include "WindowTree.h"

axMouseManager::axMouseManager()
	: _windowTree(nullptr)
	, _mouseCaptureWindow(nullptr)
	, _pastWindow(nullptr)
	, _currentWindow(nullptr)
	, _evtHasReachWindow(false)
	, _scrollCaptureWindow(nullptr)
{
}

void axMouseManager::SetWindowTree(ax::WindowTree* tree)
{
	_windowTree = tree;
}

bool axMouseManager::IsEventReachWindow() const
{
	return _evtHasReachWindow;
}

void axMouseManager::VerifyAndProcessWindowChange()
{
	if (_pastWindow != _currentWindow) {
		ax::Window* last_past = _pastWindow;
		_pastWindow = _currentWindow;

		// Mouse leave event first.
		if (last_past != nullptr) {
			last_past->event.OnMouseLeave(_mousePosition);
			
			/// @todo This is called a lot for nothing.
			/// 	  Realy not a good idea but practical.
			ax::Window* win = last_past->node.GetParent();
			
			while(win) {
				win->event.OnMouseLeaveChild(_mousePosition);
				win = win->node.GetParent();
			}
		}

		// Then mouse enter event.
		if (_currentWindow != nullptr) {
			_currentWindow->event.OnMouseEnter(_mousePosition);
			
			// Enter one of child window.
			ax::Window* win = _currentWindow->node.GetParent();
			
			/// @todo This is called a lot for nothing.
			/// 	  Realy not a good idea but practical.
			while(win) {
				win->event.OnMouseEnterChild(_mousePosition);
				win = win->node.GetParent();
			}
		}
	}
}

void axMouseManager::OnMouseLeftDragging(const ax::Point& pos)
{
	if (_mouseCaptureWindow != nullptr) {
		_mouseCaptureWindow->event.OnMouseLeftDragging(pos);
		_evtHasReachWindow = true;
	}
	else {
		_evtHasReachWindow = false;
	}
}

void axMouseManager::OnMouseMotion(const ax::Point& pos)
{
	_mousePosition = pos;

	// Only for Windows and Linux
	if (_mouseCaptureWindow != nullptr) {
		_mouseCaptureWindow->event.OnMouseLeftDragging(pos);
		_evtHasReachWindow = true;
	}
	else {
		ax::Window* win = _windowTree->FindMousePosition(pos);

		if (win != nullptr && win->property.HasProperty("Selectable")) {
			_currentWindow = win;

			if (_currentWindow != nullptr) {
				_currentWindow->event.OnMouseMotion(pos);
				_evtHasReachWindow = true;
			}
			else {
				_evtHasReachWindow = false;
			}

			VerifyAndProcessWindowChange();
		}
		else {
			_evtHasReachWindow = false;
		}
	}
}

void axMouseManager::OnMouseLeftDoubleClick(const ax::Point& pos)
{
	_mousePosition = pos;

//	ax::Print("OnMouseLeftDoubleClick");

	if (_mouseCaptureWindow != nullptr) {
//		ax::Print("Captured");
//		_mouseCaptureWindow->event.OnMouseLeftDoubleClick(pos);
//		_evtHasReachWindow = true;
	}
	else {
//		ax::Print("Not Captured");
		ax::Window* win = _windowTree->FindMousePosition(pos);

		_currentWindow = win;

		if (win != nullptr) {
			ax::Print("Win id :", win->GetId());
			win->event.OnMouseLeftDoubleClick(pos);
			_evtHasReachWindow = true;
//			ax::Print("Win not null");
		}
		else {
			_evtHasReachWindow = false;
		}

		VerifyAndProcessWindowChange();
	}
}

void axMouseManager::OnMouseLeftDown(const ax::Point& pos)
{
	_mousePosition = pos;
	
	if (_global_click_listener.size()) {
		for (auto& n : _global_click_listener) {
			ax::Window::Event::GlobalClick msg;
			msg.type = ax::Window::Event::GlobalClick::LEFT_CLICK_DOWN;
			msg.pos = pos;
			n->event.OnGlobalClick(msg);
		}
	}

	// If mouse is already grabbed.
	if (_mouseCaptureWindow != nullptr) {
		_mouseCaptureWindow->event.OnMouseLeftDown(pos);
		_evtHasReachWindow = true;
	}
	else {

		ax::Window* win = _windowTree->FindMousePosition(pos);

		if (win != nullptr && win->property.HasProperty("Selectable")) {
			_currentWindow = win;

			if (win != nullptr) {
				win->event.OnMouseLeftDown(pos);
				_evtHasReachWindow = true;
			}
			else {
				_evtHasReachWindow = false;
			}

			VerifyAndProcessWindowChange();
		}
		else {
			_evtHasReachWindow = false;
		}
	}
}

void axMouseManager::OnMouseRightDown(const ax::Point& pos)
{
	_mousePosition = pos;
	
	if (_global_click_listener.size()) {
		for (auto& n : _global_click_listener) {
			ax::Window::Event::GlobalClick msg;
			msg.type = ax::Window::Event::GlobalClick::RIGHT_CLICK_DOWN;
			msg.pos = pos;
			n->event.OnGlobalClick(msg);
		}
	}

	if (_mouseCaptureWindow) {
		_mouseCaptureWindow->event.OnMouseRightDown(pos);
		_evtHasReachWindow = true;
	}
	else {
		ax::Window* win = _windowTree->FindMousePosition(pos);
		_currentWindow = win;

		if (win != nullptr) {

			win->event.OnMouseRightDown(pos);
			_evtHasReachWindow = true;
		}
		else {
			_evtHasReachWindow = false;
		}

		VerifyAndProcessWindowChange();
	}
}

void axMouseManager::OnMouseLeftUp(const ax::Point& pos)
{
	_mousePosition = pos;

	if (_mouseCaptureWindow) {
		_currentWindow = _windowTree->FindMousePosition(pos);
		_mouseCaptureWindow->event.OnMouseLeftUp(pos);
		_evtHasReachWindow = true;
	}
	else {
		ax::Window* win = _windowTree->FindMousePosition(pos);
		_currentWindow = win;

		if (win != nullptr) {
			win->event.OnMouseLeftUp(pos);
			_evtHasReachWindow = true;
		}
		else {
			_evtHasReachWindow = false;
		}

		VerifyAndProcessWindowChange();
	}
}

void axMouseManager::OnScrollWheel(const ax::Point& delta)
{
	if(_scrollCaptureWindow == nullptr) {
		_evtHasReachWindow = false;
		return;
	}
	
	_scrollCaptureWindow->event.OnScrollWheel(delta);
	_evtHasReachWindow = true;

}

void axMouseManager::OnMouseRightUp()
{
	_evtHasReachWindow = false;
}

void axMouseManager::ReleaseMouseHover()
{
	_currentWindow = nullptr;
	_pastWindow = nullptr;
}

void axMouseManager::GrabMouse(ax::Window* win)
{
	_mouseCaptureWindow = win;
}

void axMouseManager::UnGrabMouse()
{
	_mouseCaptureWindow = nullptr;
}

bool axMouseManager::IsGrab() const
{
	return (_mouseCaptureWindow != nullptr);
}

bool axMouseManager::IsMouseHoverWindow(const ax::Window* win) const
{
	return (win == _currentWindow);
}

bool axMouseManager::IsMouseStillInChildWindow(const ax::Window* win) const
{
	ax::Window* w = _currentWindow;

	while (w != nullptr) {
		if (w == win) {
			return true;
		}

		w = w->node.GetParent();
	}

	return false;
}

void axMouseManager::SetPastWindow(ax::Window* win)
{
	_pastWindow = win;
}

void axMouseManager::AddGlobalClickListener(ax::Window* win)
{
	// Check if window is already in global listener.
	for (auto& n : _global_click_listener) {
		if (n->GetId() == win->GetId()) {
			return;
		}
	}

	_global_click_listener.push_back(win);
}

void axMouseManager::RemoveGlobalClickListener(ax::Window* win)
{
	int index = -1;
	// Check for window index.
	for (int i = 0; i <_global_click_listener.size(); i++) {
		if (_global_click_listener[i]->GetId() == win->GetId()) {
			index = i;
			break;
		}
	}
	
	if(index != -1) {
		_global_click_listener.erase(_global_click_listener.begin() + index);
	}
}