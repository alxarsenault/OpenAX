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
 
#ifndef __AX_WINDOW_TREE__
#define __AX_WINDOW_TREE__

/// @defgroup Core
/// @{

#include "Utils.h"
#include "Window.h"
#include <map>
#include <deque>

namespace ax {

/*
 * WindowTree
 */
class WindowTree {
public:
	WindowTree();

	void AddTopLevel(ax::Window::Ptr win);
//	void AddTopLevel(ax::Window* win);

	ax::Window::Ptr GetTopLevel();

	/// Get all window parent's from top to bottom.
	/// Index [0] is the older parent of the window after
	/// frame window. So if the window is a direct child from
	/// frame window the size of the deque is null.
	std::deque<ax::Window::Ptr> GetWindowParents(ax::Window::Ptr win);

	/// Find the window on wich the mouse position is over.
	ax::Window* FindMousePosition(const ax::Point& pos);

	void Draw();
	
	std::vector<ax::Window::Ptr>& GetNodeVector();

private:
	std::vector<ax::Window::Ptr> _nodes;
};
}

/// @}
#endif //__AX_WINDOW_TREE__