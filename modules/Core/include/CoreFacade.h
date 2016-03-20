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

#ifndef __axLib__axCoreFacade__
#define __axLib__axCoreFacade__

#include "Utils.h"
#include <string>

class axCore;

namespace ax {
namespace Core {

	class WindowManager;

	class Facade {
	public:
		Facade(const ax::Size& frame_size);
		
		Facade(const ax::Size& frame_size, axCore* core);

		void Init(const ax::Size& frame_size);

		std::string GetAppDirectory();

		std::string GetAppPath();

		std::string OpenFileDialog();

		ax::Rect GetScreenRect();

		ax::Size GetScreenSize();

		ax::Size GetFrameSize() const;

		void SetFrameSize(const ax::Size& size);

		ax::Core::WindowManager* GetWindowManager();

		ax::Core::WindowManager* GetPopupManager();

		ax::Core::WindowManager* GetRealPopWindowManager();

		void UpdateAll();

		void HideMouse();

		void ShowMouse();

		int Draw();

		virtual void MainLoop();

		void SetCursor(const int& cursor_id);
		
		void SetResizable(bool resizable);
		
		void SetTitleBar(bool titlebar);
		
		void SetFocusAndCenter();

		/// ax::App -> ax::Core::Facade should be use instead of this.
		/// Better know what you are doing when you're using this function.
		axCore* GetCore();

	protected:
		void PushEventOnSystemQueue();

	private:
		axCore* _core;
	};
}
}

#endif /* defined(__axLib__axCoreFacade__) */
