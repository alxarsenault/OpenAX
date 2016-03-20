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
 
#ifndef __AX_CORE__
#define __AX_CORE__

/// @defgroup Core
/// @{

#include "WindowManager.h"
#include <time.h>
#include <memory>

class axCore {
public:
	axCore();

	virtual void MainLoop() = 0;

	virtual void Init(const ax::Size& frame_size) = 0;

	virtual void ResizeGLScene(const ax::Size& size);

	virtual bool CreateGLWindow(const char* title, int width, int height, int bits) = 0;

	virtual std::string GetAppDirectory() = 0;

	virtual std::string GetAppPath()
	{
		return "";
	}

	virtual ax::Rect GetScreenRect() = 0;

	virtual ax::Size GetScreenSize() = 0;

	virtual std::string OpenFileDialog() = 0;

	virtual void PushEventOnSystemQueue() = 0;

	virtual void ResizeFrame(const ax::Size& size) = 0;

	virtual void KillGLWindow() = 0;

	int InitGL();

	virtual void SetCursor(const int& cursor_id)
	{
		ax::Print("axCore set cursor");
	}

	virtual ax::Core::WindowManager* GetWindowManager();

	virtual ax::Core::WindowManager* GetPopupManager();

	virtual ax::Core::WindowManager* GetRealPopWindowManager();
	
	virtual ax::Core::WindowManager* GetEditorWindowManager()
	{
		return _editor_manager.get();
	}

	ax::Size GetGlobalSize() const;

	void SetGlobalSize(const ax::Size& size);

	virtual void UpdateAll();

	virtual void HideMouse()
	{
	}

	virtual void ShowMouse()
	{
	}
	
	virtual void SetResizable(bool resizable)
	{
	}
	
	virtual void SetTitleBar(bool titlebar)
	{
	}
	
	virtual void SetFocusAndCenter()
	{
		
	}

	virtual int DrawGLScene();
	
//	virtual void SetMouseCursor(int cursor_id)
//	{
//		
//	}

protected:
	std::unique_ptr<ax::Core::WindowManager> _windowManager;
	std::unique_ptr<ax::Core::WindowManager> _popupManager;
	std::unique_ptr<ax::Core::WindowManager> _editor_manager;
	
	std::unique_ptr<ax::Core::WindowManager> _realPopWindowManager;

	bool _needToDraw, _popupNeedToDraw;
	ax::Size _size, _popSize;
	int _cursor_id;

	virtual void InitManagers();
};

/// @}
#endif //__AX_CORE__
