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

#include "KeyboardManager.h"
#include "Window.h"
#include "WindowTree.h"

axKeyboardManager::axKeyboardManager()
	: _windowTree(nullptr)
	, _keyGrabbedWindow(nullptr)
	, _isCmdDown(false)
{
}

void axKeyboardManager::SetWindowTree(ax::WindowTree* tree)
{
	_windowTree = tree;
}

void axKeyboardManager::AddGlobalGrabedWindow(ax::Window* win)
{
	_globalKeyGrabbed.push_back(win);
}

bool axKeyboardManager::IsCmdDown() const
{
	return _isCmdDown;
}

void axKeyboardManager::OnKeyDown(const char& key)
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnKeyDown(key);
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnKeyDown(key);
	}
}

void axKeyboardManager::OnEnterDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnEnterDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnEnterDown('0');
	}
}

void axKeyboardManager::OnKeyUp(const char& key)
{
}

void axKeyboardManager::OnBackSpaceDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnBackSpaceDown('0');
	}
}

void axKeyboardManager::GrabKey(ax::Window* win)
{
	if (_keyGrabbedWindow != win) {
		if (_keyGrabbedWindow != nullptr) {
			_keyGrabbedWindow->event.OnWasKeyUnGrabbed('0');
		}

		win->event.OnWasKeyGrabbed('0');
	}

	_keyGrabbedWindow = win;
}

void axKeyboardManager::UnGrabKey()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnWasKeyUnGrabbed('0');
		_keyGrabbedWindow = nullptr;
	}
}

bool axKeyboardManager::IsKeyGrab(const ax::Window* win) const
{
	return (win == _keyGrabbedWindow);
}

void axKeyboardManager::OnLeftArrowDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnLeftArrowDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnLeftArrowDown('0');
	}
}

void axKeyboardManager::OnRightArrowDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnRightArrowDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnRightArrowDown('0');
	}
}

void axKeyboardManager::OnUpArrowDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnUpArrowDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnUpArrowDown('0');
	}
}

void axKeyboardManager::OnDownArrowDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnDownArrowDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnDownArrowDown('0');
	}
}

void axKeyboardManager::OnKeyDeleteDown()
{
	if (_keyGrabbedWindow != nullptr) {
		_keyGrabbedWindow->event.OnKeyDeleteDown('0');
	}
	
	for(auto& n : _globalKeyGrabbed) {
		n->event.OnKeyDeleteDown('0');
	}
}

void axKeyboardManager::OnCmdDown()
{
	_isCmdDown = !_isCmdDown;

	if (_keyGrabbedWindow != nullptr) {
		if(_isCmdDown) {
			_keyGrabbedWindow->event.OnCmdDown('0');
		}
		else {
			_keyGrabbedWindow->event.OnCmdUp('0');
		}
	}
	
	for(auto& n : _globalKeyGrabbed) {
		if(_isCmdDown) {
			n->event.OnCmdDown('0');
		}
		else {
			n->event.OnCmdUp('0');
		}
	}
}
