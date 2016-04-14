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

#ifndef __AX_MOUSE_MANAGER__
#define __AX_MOUSE_MANAGER__

/// @defgroup Core
/// @{

#include "Utils.h"
#include "Window.h"

namespace ax {
class WindowTree;

namespace core {

	// class axWindowTree;

	class MouseManager {
	public:
		MouseManager();

		void SetWindowTree(ax::WindowTree* tree);

		// Mouse events.
		void OnMouseMotion(const ax::Point& pos);
		void OnMouseLeftDragging(const ax::Point& pos);
		void OnMouseLeftDown(const ax::Point& pos);
		void OnMouseLeftDoubleClick(const ax::Point& pos);
		void OnMouseLeftUp(const ax::Point& pos);
		void OnMouseRightDown(const ax::Point& pos);
		void OnMouseRightUp();
		void GrabMouse(ax::Window* win);
		void UnGrabMouse();

		void OnScrollWheel(const ax::Point& delta);

		bool IsGrab() const;
		bool IsMouseHoverWindow(const ax::Window* win) const;
		bool IsEventReachWindow() const;

		bool IsMouseStillInChildWindow(const ax::Window* win) const;

		void ReleaseMouseHover();

		void SetScrollCaptureWindow(ax::Window* win)
		{
			_scrollCaptureWindow = win;
		}

		void ReleaseScrollCaptureWindow()
		{
			_scrollCaptureWindow = nullptr;
		}

		/// Set the last window for mouse enter and leave functions.
		/// Be careful with this function, it might break the user app logic.
		void SetPastWindow(ax::Window* win);

		void AddGlobalClickListener(ax::Window* win);
		void RemoveGlobalClickListener(ax::Window* win);

	private:
		ax::WindowTree* _windowTree;

		// Mouse.
		ax::Window* _mouseCaptureWindow;
		ax::Window* _pastWindow;
		ax::Window* _currentWindow;
		ax::Window* _scrollCaptureWindow;
		ax::Point _mousePosition;

		bool _evtHasReachWindow;

		std::vector<ax::Window*> _global_click_listener;

		void VerifyAndProcessWindowChange();
	};
}
}

/// @}
#endif //__AX_MOUSE_MANAGER__
