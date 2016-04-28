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
#include <deque>
#include <map>

namespace ax {
namespace core {
	/*
	 * WindowTree
	 */
	class WindowTree {
	public:
		WindowTree();

		void AddTopLevel(std::shared_ptr<ax::Window> win);

		std::shared_ptr<ax::Window> GetTopLevel();

		/// Get all window parent's from top to bottom.
		/// Index [0] is the older parent of the window after
		/// frame window. So if the window is a direct child from
		/// frame window the size of the deque is null.
		std::deque<std::shared_ptr<ax::Window>> GetWindowParents(std::shared_ptr<ax::Window> win);

		/// Find the window on wich the mouse position is over.
		ax::Window* FindMousePosition(const ax::Point& pos);

		void Draw();

		std::vector<std::shared_ptr<ax::Window>>& GetNodeVector();

		void Operation(ax::Window* window, std::function<void(ax::Window*)> fct);
		
		void OperationOnChild(ax::Window* window, std::function<void(ax::Window*)> fct);
		
		ax::Window* FirstFind(ax::Window* window, std::function<bool(ax::Window*)> fct);
		
		ax::Window* FirstFindOnChild(ax::Window* window, std::function<bool(ax::Window*)> fct);

//		std::vector<ax::Window*> WidgetAcumulator(
//			ax::Window* window, std::function<bool(ax::Window*)> fct)
//		{
//			std::vector<ax::Window*> widget_accumulator;
//			
//			if (window == nullptr) {
//				return widget_accumulator;
//			}
//			
//			fct(window);
//			
//			std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
//			
//			for (auto& n : children) {
//				if(WidgetFirstFind(n.get(), fct)) {
//					return n.get();
//				}
//			}
//			
//			return nullptr;
//		}

	private:
		std::vector<std::shared_ptr<ax::Window>> _nodes;

//		void WidgetAcumulatorRecursive(ax::Window* window, std::vector<ax::Window*>& widget_accumulator,
//			std::function<bool(ax::Window*)> fct)
//		{
//			if (window == nullptr) {
//				return;
//			}
//
//			fct(window);
//
//			std::vector<std::shared_ptr<ax::Window>>& children = window->node.GetChildren();
//
//			for (auto& n : children) {
//				ax::Window* tmp = WidgetFirstFind(n.get(), fct);
//
//				if (tmp != nullptr) {
//					return tmp;
//				}
//			}
//
//			return nullptr;
//		}
	};
}
}

/// @}
#endif //__AX_WINDOW_TREE__